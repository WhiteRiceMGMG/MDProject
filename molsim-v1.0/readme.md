Features
 - Basic molecular dynamics simulation
 - Velocity-Verlet integration
 - Lennard-Jones potential
 - Configurable time step, particle count
 - File output for trajectories 

Build & Run
 - GCC | Clang
 - Make (optional)
 - A posix compliant environment Linux, WSL, macOS

Compile
 - gcc -o md_sim src/main.c src/particle.c src/simulation.c -lm
 