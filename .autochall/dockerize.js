import chalk from 'chalk';
import input from 'input';

import { existsSync, copyFileSync, writeFileSync, readFileSync } from "fs";
import challs from "./lib/challs.js";
import { dirname, join } from 'path';
import { fileURLToPath } from 'url';
import { stringify } from 'yaml';

const __dirname = dirname(fileURLToPath(import.meta.url));

const dir = process.argv[0].endsWith("node") ? process.argv[2] : process.argv[1];

console.error = (log, ...a) => console.log(chalk.bgRedBright("ERR] " + log), ...a);

if (typeof dir !== "string") {
    console.error("`node dockerize <challenge folder name>`");
    process.exit();
}

const chall = challs.find(c => c.dir === dir);

if (!chall) {
    console.error("Unexistant challenge id");
    process.exit();
}


const createBinexDocker = async (chall) => {
    let srcFile = await input.text("src file? ", { default: 'src.c' });
    while (!existsSync(join(chall.path, srcFile))) {

        console.log("This file does not exist...");
        if (await input.confirm("Continue anyway? ", {default: "N"})) break;

        srcFile = await input.text("new src file? ", { default: 'src.c' });
    }
    const outFile = await input.text("out file? ", { default: 'chall' });
    const buildArgs = await input.text("build args? ");

    copyFileSync(join(__dirname, "./ynetd"), join(chall.path, "./ynetd"));
    console.log(chalk.gray("[!] Copied ynetd"))
    writeFileSync(join(chall.path, "Dockerfile"), `FROM --platform=linux/amd64 ubuntu@sha256:86ac87f73641c920fb42cc9612d4fb57b5626b56ea2a19b894d0673fd5b4f2e9 AS build

RUN apt-get update -y && \
apt-get install -y gcc && \
rm -rf /var/lib/apt/lists/*

COPY ${srcFile} .
RUN gcc -o ${outFile} ${(buildArgs + " ").trimStart()}${srcFile}


FROM --platform=linux/amd64 ubuntu@sha256:86ac87f73641c920fb42cc9612d4fb57b5626b56ea2a19b894d0673fd5b4f2e9

RUN useradd -m -d /home/ctf -u 12345 ctf
WORKDIR /home/ctf

COPY ynetd .
RUN chmod +x ynetd

COPY --from=build ${outFile} ${outFile}
COPY flag.txt .

RUN chown -R root:root /home/ctf

USER ctf
EXPOSE 9999
CMD ./ynetd -p 9999 ./${outFile}`);
    console.log(chalk.gray("[!] Copied Dockerfile"));

    const challMeta = {...chall};
    delete challMeta.path;
    delete challMeta.dir;

    challMeta.deploy = {nc: {build: ".", expose: "9999/tcp"}};

    writeFileSync(join(chall.path, "chall.yaml"), stringify(challMeta));

    console.log(chalk.gray("[!] Modified chall yaml"));
    
    console.log(chalk.greenBright("Docker set up!"))
}

const createPyWebDocker = async (chall) => {
    if (!existsSync(join(chall.path, "app.py"))) {
        console.error("app.py NOT FOUND. Make sure python code is in app.py");
        return;
    }
    if (!(await input.confirm("Please confirm that the server code is inside of " + chall.dir + "/app.py"))) {
        console.error("Please make necessary changes to challenge");
        return;
    }
    if (!existsSync(join(chall.path, "requirements.txt"))) {
        console.error("requirements.txt NOT FOUND. Please add necessary lib and their versions (ex, Flask)");
        return;
    }
    if (!(await input.confirm("Please confirm that the server code will listen on PORT 5000"))) {
        console.error("Please make necessary changes to challenge");
        return;
    }
    if (!(await input.confirm("Please confirm that the server code does not allow for REMOTE CODE EXECUTION", {default:"Y"}))) {
        console.error("Please make necessary changes to challenge and or make a custom dockerfile");
        return;
    }

    writeFileSync(join(chall.path, "Dockerfile"), `FROM --platform=linux/amd64 python:3.8-slim-buster
WORKDIR /app

# install dependencies
COPY requirements.txt requirements.txt
RUN pip3 install -r requirements.txt

# copy over source
COPY . .

# run and expose
EXPOSE 5000
CMD ["python3", "-m" , "flask", "run", "--host=0.0.0.0", "--port=5000"]`);
console.log(chalk.gray("[!] Copied Dockerfile"));
    const challMeta = {...chall};
    delete challMeta.path;
    delete challMeta.dir;

    challMeta.deploy = {web: {build: ".", expose: "5000/tcp"}};
    console.log(chalk.gray("[!] Modified chall.yaml"));

    writeFileSync(join(chall.path, "chall.yaml"), stringify(challMeta));
}

const createNodeWebDocker = async (chall) => {
    let dir = await input.text("Path of server? ", {default: "."});
    if (!existsSync(join(chall.path, dir, "package.json"))) {
        console.error("package.json NOT FOUND. Are you sure there is a package here?");
        return;
    }
    if (!existsSync(join(chall.path, dir, "package-lock.json"))) {
        console.error("package-lock.json NOT FOUND. Please remember to install to allow for package-lock.json to formulate");
        return;
    }
    try {
        const pkg = JSON.parse(readFileSync(join(chall.path, dir, "package.json"), 'utf-8'));
        if (!pkg.scripts || !pkg.scripts.start) {
            console.error("`npm run start` could not be found. Please add a start script to your package json.");
            return;
        }
    } catch {
        console.error("package.json could not be parsed. Please double check your package json");
        return;
    }
    if (!(await input.confirm("Please confirm that the server code will listen on PORT 3000"))) {
        console.error("Please make necessary changes to challenge");
        return;
    }
    if (!(await input.confirm("Please confirm that the server code does not allow for REMOTE CODE EXECUTION"))) {
        console.error("Please make necessary changes to challenge and or make a custom dockerfile");
        return;
    }

    writeFileSync(join(chall.path, "Dockerfile"), `FROM --platform=linux/amd64 node:16

# Copy package files
WORKDIR /usr/src/app
COPY ${dir}/package*.json ./${dir}/

# Install dependencies
WORKDIR ${join('/usr/src/app/', dir)}
RUN npm ci

# Copy rest of files
WORKDIR /usr/src/app
COPY . .

# Run "npm build"
WORKDIR ${join('/usr/src/app/', dir)}
RUN npm run build --if-present

# Expose port and run server
EXPOSE 3000
CMD ["npm", "start"]`);
console.log(chalk.gray("[!] Copied Dockerfile"));

    const challMeta = {...chall};
    delete challMeta.path;
    delete challMeta.dir;

    challMeta.deploy = {web: {build: ".", expose: "3000/tcp"}};

    writeFileSync(join(chall.path, "chall.yaml"), stringify(challMeta));
    console.log(chalk.gray("[!] Modified chall.yaml"));
}

let valid = true;
switch (true) {
    case chall.categories.includes("binex"): {
        console.log(chalk.bold("Detected ") + chalk.bold.bgCyanBright("BINEX") + chalk.reset.bold(" challenge\n"));
        await createBinexDocker(chall);
    } break;
    case chall.categories.includes("webex"): {
        console.log(chalk.bold("Detected ") + chalk.bold.bgMagentaBright("WEBEX") + chalk.reset.bold(" challenge\n"));
        const type = await input.select("Choose app type", ["node", "python", "other"]);
        if (type === "other") {
            console.error("Only supports NODE and PYTHON. Goodbye!");
            process.exit(1);
        } else if (type === "python") {
            await createPyWebDocker(chall);
        } else if (type === "node") {
            await createNodeWebDocker(chall);
        }
    } break;
    default: {
        console.error("Unsupported challenge type");
        valid = false;
    } break;
}

if (valid) {
    console.log(chalk.greenBright("Docker set up!"));
}
