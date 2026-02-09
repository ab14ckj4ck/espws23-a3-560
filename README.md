# espws23-a3-560

# Assignment 3 - SyntaxSakura

## Introduction

In Assignment 3 (A3) of the ESP practicals (KU), you will implement a card game for two
players, which is loosely inspired by [Ohanami](https://de.wikipedia.org/wiki/Ohanami).
Please take care to follow the assignment description exactly, even if you know the original game, becaus>
uses different rules than the original and even slight differences in your implementation can cause
testcases to fail.

This document describes the structure of the assignment and the expected functionality of the program.

## Learning  Goals

- Heap and Memory Management
- File I/O
- Structs
- Enums
- Linked Lists

## Specifications

Some general specifications must be followed for every assignment in this course. A list of these specifi>
[Assessment of Assignments - Deductions](https://www.notion.so/coding-tugraz/Assessment-of-Assignments-Ho>

Additionally, the following specifications must be followed for this assignment (A3) as well:
* **Attention:** Each card in the game has to be represented as a **struct**. These structs should hold a>
* **Attention:** All cards must be stored **on the heap**. If this is not the case, this will result in a>
* **Attention:** All rows of cards in the game, including hand cards, chosen cards and rows of cards that>
* **Attention:** As the user input can be of arbitrary length, it must be read in dynamically using **rea>

## Grading

Assignment 3 is worth **40 points**.

**Attention:** To receive a positive grade on the ESP KU **at least 6 of the public test cases have to be>

Information on how your assignment submission will be assessed can be found here: [Assessment of Assignme>
Please read this carefully as it also contains guidelines on what your final code should look like (Codin>

Here you can find an overview of how your total grade for the KU will be calculated: [Procedure and Gradi>

## Submission
- Deliverables: `a3.c`
- Push to your repository
