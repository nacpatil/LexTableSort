# Lexical Sorting Algorithm

## Algorithm Used

1. **Sort the n-th vector shards**  
   - Use shards from the **(n-1)th** vector.  
   - Update the **permutation vector** obtained from the previous step.  

2. **Apply the permutation**  
   - Apply the permutation from step 1 to the **(n+1)th** vector.  

3. **Compute new shards**  
   - Check each **old shard** and see if there are **repeats**.  
   - If numbers repeat, they form a **single shard** together.  
   - Unique numbers each form their own shard.  

4. **Repeat step 1**  
   - Continue the sorting process until all columns are processed.  

---

## What are Shards?
> **Shards** are **segments of a vector** derived from sorting the previous vector.  
> - If values **repeat**, then together they make a single shard.  
> - If all values are **unique**, each value becomes a **separate shard**.  

---

## Computational Complexity

### **Worst-Case Complexity (Unsorted Data)**
- **Each vector sort:** O(n log n) (using `std::sort` with a comparator).  
- **Sorting the whole table:** O(m * n log n).  
  - **n** = Number of rows  
  - **m** = Number of columns  

### **Best-Case Complexity (Already Sorted Data)**
- **Each vector sort:** O(n).  
- **Sorting the whole table:** O(m * n).  

---

## **Memory Complexity**
- **Formula:** O(n).  
- **Explanation:**
  - Uses two additional vectors.
  - Becomes **smaller** if data has repeated values.
  - For **large datasets with multiple columns**, overhead is negligible.

---

## **Assumptions**
- **All vectors must be of the same size.**
- The algorithm **can be modified** to handle unequal-sized vectors.

---

## **Error Handling**
- **Unequal vector sizes in `Table` constructor**  
  - Throws an intentional `std::runtime_error` to **stop execution**.  
  - Needs **better handling** for real-world applications.  

- **Empty input handling**  
  - If the input is **empty**, it simply creates an **empty table**.  
  - Sorting does **nothing** if called on an empty table.  
  - Ideally, a **warning should be issued** in such cases.

## **Testing**
- **10 tests are included and run automatically when code is executed.**  
- Edge cases such as all values being same  
- No data entered at all  
- Some standard cases where multiple vectors break in shrads over multiple columns.  