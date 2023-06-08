#!/usr/bin/python3

import argparse
import sys
import time
import pygame
from numpy import array_split

def hash_to_grid(hash, size):
    bits = []

    for ch in hash:
        bits.extend(bin(int(ch, 16))[2:].zfill(4))

    # Trim zero padding and convert into booleans
    bits = bits[:size**2]
    bits = [bool(int(b)) for b in bits]

    return array_split(bits, size)

# Read input
parser = argparse.ArgumentParser()
parser.add_argument("--size", type=int, help="Size of the grid")
parser.add_argument("--speed", type=int, help="In miliseconds", default=500)
args = parser.parse_args()

lines = sys.stdin.read().splitlines()
data = []

for line in lines:
    parts = line.split(',')
    el = {}

    for part in parts:
        el[part.split('=')[0]] = part.split('=')[1]

    data.append(el)

# Init window
pygame.init()
screen_size = 800
margin = 50
bg_color = (77, 77, 77)
font = pygame.font.SysFont("Arial", 26)
cell_size = (screen_size - margin * 2) / args.size
screen = pygame.display.set_mode((screen_size, screen_size))
hash_index = 0
grid = hash_to_grid(data[hash_index]['h'], args.size)
timer = pygame.time.get_ticks()

# Draw
while True:
    # Background
    screen.fill(bg_color)

    # Header
    text = "Step {}/{}, errors {}".format(int(data[hash_index]['i']) + 1, len(data), data[hash_index]['e'])
    text_rendered = font.render(text, True, (255, 255, 255))
    screen.blit(text_rendered, (margin, 10))

    # Cells
    for y, row in enumerate(grid):
        for x, cell in enumerate(row):
            color = (0, 0, 0) if cell else (255, 255, 255)

            pygame.draw.rect(screen, color, (x * cell_size + margin, y * cell_size + margin, cell_size, cell_size))

    # Grid
    for i in range(args.size):
        pygame.draw.line(screen, bg_color, (margin, margin + i * cell_size), (screen_size - margin, margin + i * cell_size))
        pygame.draw.line(screen, bg_color, (margin + i * cell_size, margin), (margin + i * cell_size, screen_size - margin))

    if hash_index < len(data) - 1 and pygame.time.get_ticks() - timer >= args.speed:
        hash_index += 1
        grid = hash_to_grid(data[hash_index]['h'], args.size)
        timer = pygame.time.get_ticks()

    # Event handling
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

    pygame.display.flip()