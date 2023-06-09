#!/bin/bash

rm -r ./build
mkdir ./build
mkdir ./build/temp

echo "Copying code"
cp -r ./flag.txt ./package.json ./tsconfig.json                                     ./build
cp -r ./base ./chall ./server ./solve ./flag.txt ./package.json ./tsconfig.json     ./build/temp

cd ./build

echo "Installing packages"
npm i

echo "Substituting parameters"
sed 's/=.\{1,\}POWER_PRIME/= '$POWER_PRIME';/g' ./temp/base/hashing.ts > ./temp/base/hashing1.ts
sed 's/=.\{1,\}MOD_PRIME/= '$MOD_PRIME';/g' ./temp/base/hashing1.ts > ./temp/base/hashing2.ts
cp ./temp/base/hashing2.ts ./temp/base/hashing.ts
rm ./temp/base/hashing1.ts ./temp/base/hashing2.ts


# Calculate and interpolate the generated repository
echo "Prebuilding repository"
USE_PRESETS=true npx ts-node ./temp/chall/gen_export.ts > ./temp/prebuilt.js
USE_PRESETS=true npx ts-node ./temp/chall/gen_export_block.ts > ./lost_block.txt

echo "Formatting prebuilt data"
echo 'const recievedBlocks: [bigint, string][] = ' "$(cat ./temp/prebuilt.js)" ';' > ./temp/prebuilt.js

echo "Substituting data"
sed '/import recievedBlocks from "\.\.\/chall\/gen";/r ./temp/prebuilt.js' ./temp/server/index.ts > ./temp/server/index1.ts
sed '/import recievedBlocks from "\.\.\/chall\/gen";/d' ./temp/server/index1.ts > ./temp/server/index2.ts
cp ./temp/server/index2.ts ./temp/server/index.ts
rm ./temp/server/index1.ts ./temp/server/index2.ts

# Copy the relevant folders
echo "Copying relevant data"
cp -r ./temp/base ./base
cp -r ./temp/server ./server

# Remove the extra build stuff
echo "Removing extra build artifacts"
rm -rf ./temp


