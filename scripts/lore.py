#!/usr/bin/env python3

for lore in range(6):
    for lore_level in range(6):
        #percent = 100 * (lore) / (lore_level + 1)
        #percent = 50 + 10 * (lore - lore_level)
        percent = (20 * lore) * (lore + 1) / (lore_level + 1)
        print(f"Lore {lore}, Lore Level {lore_level} -> {percent} %")

