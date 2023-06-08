import challs from "./lib/challs.js";

const byCategory = Object.create(null);

for (const chall of challs) {
    const c = chall.categories[0];
    if (chall.categories.length > 1) console.warn("Skipping multiple categories (" + chall.categories.join(", ") + ") for " + chall.name + " and continueing with " + c);
    if (!byCategory[c]) byCategory[c] = [chall];
    else byCategory[c].push(chall);


    if (!chall.value) {
        console.log(chall.name + " missing value");
    }
}

const table = {};

for (const category in byCategory) {
    const challs = byCategory[category];
    const data = table[category] = {};

    data.count = challs.length;
    data.maxval = challs.reduce((V, b) => b.value > V ? b.value : V, 0);
    data.minval = challs.reduce((V, b) => b.value > V ? V : b.value, Infinity);
    data.avgval = challs.reduce((V, b) => V + b.value, 0) / challs.length;
    data.avgval = Math.round(data.avgval);
}


console.table(table)