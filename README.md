# Neroli

Neroli is an experimental fork of [Azahar Emulator](https://github.com/azahar-emu/azahar) ported to run on the Nintendo Wii U. This currently aims to run FastInterp and the software renderer.

## Building

- Install Docker/Git
  - This setup guide uses the `devkitpro/devkitppc` Docker image but that isn't required
- Clone the repository: 

```sh
git clone --recursive https://github.com/aminoa/neroli.git
```

- From the repository root, run the CI build script inside the devkitPPC container:

```sh
./tools/enter-docker-dev-container/wiiu.sh ./.ci/wiiu.sh
```
