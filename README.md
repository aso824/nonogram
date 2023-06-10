# Nonogram heuristic solver

## Intro

Goal is to implement common metaheuristic methods to solve, or at least try to solve, puzzles called Nonograms.

## Available algorithms

- Hillclimb
- Random hillclimb
- Genetic
- Tabu

## How to run

    ./nonogram [file] [algorithm]

For example: `./nonogram data/simple.txt tabu`

There is flag `--steps` that will show each step with hash and score. Can be used with Python script to render progress:

    ./nonogram data/simple.txt tabu --steps | ./scripts/steps.py --size=5 --speed=50

## Summary

Hillclimb algorithm hits the local optimum very fast, which doesn't solve Nonogram.  
Genetic sometimes founds solution, but in most cases it fails to find a solution within specified time.  
Best one is tabu, which solves 5x5 nonogram in average of 50 to 200 iterations.

Probably improving goal function to return float as error count instead of integer could help.