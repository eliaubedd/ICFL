
# 📚 Construction of a Suffix Array from Inverse Lyndon Factorization

**Author:** Elia Leonardo Martin (matricola 886366)  
**Supervisors:** Prof. Raffaella Rizzi (Advisor), Prof. Paola Bonizzoni (Co-advisor)  
**Institution:** University of Milano-Bicocca – Department of Computer Science, Systems and Communication  
**Academic Year:** 2023–2024

---

## 🧠 Project Overview

This thesis explores a novel algorithmic approach to the construction of the **Suffix Array** of a string, based on its **Inverse Lyndon Factorization (ICFL)**. Suffix Arrays are efficient data structures that support fast pattern matching operations; however, their construction is still computationally challenging.

This work provides a theoretical and practical framework for building the suffix array from ICFL by:
- Formalizing the concept of **local and global suffixes**
- Designing tree-based structures for suffix management
- Implementing optimized algorithms in C++

---

## 📖 Theoretical Foundation

### Suffix Arrays
Given a totally ordered alphabet Σ, the **Suffix Array** of a string T is an array of integers representing the starting positions of the lexicographically ordered suffixes of T.

### Inverse Lyndon Factorization (ICFL)
A string S ∈ Σ⁺ can be uniquely factorized into a sequence of **Inverse Lyndon words**:
$
ICFL(S) = m_1, m_2, ..., m_k
$
Each $m_i$ satisfies $m_i \ll m_{i+1}$, and preserves essential border properties that facilitate suffix ordering.

### Local vs Global Suffixes
- **Local suffixes** are suffixes of individual ICFL factors.
- **Global suffixes** are derived from their corresponding positions in the original string.

Key theorems demonstrate how local suffix ordering can be extended to global suffix ordering, providing the basis for tree-based suffix arrangement.

---

## ⚙️ Algorithmic Strategy

### Data Structures
- **Bitvectors** track the occurrence of suffixes across factors using `rank1` and `select1` operations.
- **Prefix-chains** and a **Prefix-tree** structure organize local suffixes hierarchically for efficient construction.

### Core Algorithms
1. `GetInsertionTarget`: Determines the insertion point for new suffixes based on local/global ordering.
2. `BuildPrefixTree`: Constructs a prefix-tree from ICFL factors using bitvectors and suffix mapping.
3. `BuildSuffixArray`: Traverses the prefix-tree bottom-up to generate the final Suffix Array.

---

## 💻 Implementation Details

### Language and Libraries
- **Language:** C++20
- **Libraries:**
  - Standard: `<iostream>`, `<fstream>`, `<vector>`, `<string>`, `<list>`, `<unordered_map>`
  - External: [`pasta/bitvector`](https://github.com/pasta-toolbox/bit_vector)

### Project Structure
- `main.cpp`: Entry point and test routines
- `func.hpp`: Core functions and algorithmic logic
- `Node.hpp`: Definition of prefix-tree nodes
- `Tree.hpp`: Suffix tree structure
- `input.txt`: Contains the ICFL of the target string

### Execution Flow
1. Read ICFL from file
2. Build prefix-tree from ICFL
3. Generate Suffix Array via post-order traversal

---

## 📊 Observations

- **Memory Management:** Special care taken to avoid leaks; some modifications to `bitvector.hpp` required to support const iterators.
- **Scalability Issues:** As the number of ICFL factors grows, tree construction and traversal become computationally expensive.

---

## ✅ Results and Conclusion

This project demonstrates the feasibility of building a suffix array using **Inverse Lyndon Factorization**. The integration of border-based suffix properties with efficient data structures like bitvectors enables a modular and theoretically grounded suffix sorting strategy.

The approach successfully bridges theoretical insights with practical implementation, yielding a valid and efficient construction pipeline in C++.

---

## 📚 References

1. Bonizzoni et al., *Inverse Lyndon Words and Factorizations*, Applied and Applied Mathematics, 2018  
2. Bonizzoni et al., *Numeric Lyndon-based Feature Embedding*, Information Sciences, 2022  
3. Cleary & Witten, *Adaptive Coding and Partial String Matching*, IEEE Transactions, 1984  
4. Gawrychowski & Kociumaka, *Lyndon Factorization of Trees*, 2012  
5. Golynski, *Lower Bounds for Rank and Select*, TCS, 2007  
6. High-Order Entropy-Compressed Text Indexes, KU ScholarWorks  
7. Manber & Myers, *Suffix Arrays: New Method for On-line String Searches*, SODA 1990  
8. Bonizzoni et al., *Properties of Inverse Lyndon Factorizations*, TCS, 2021  
9. [`pasta-toolbox/bit_vector`](https://github.com/pasta-toolbox/bit_vector)


