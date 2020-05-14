Brute Force: O(N^3)

    for element1 - O(N)
  
      for element2 - O(N)
    
        calculate which side - O(N)
      

  
Graham Scan: O(NlogN)

    find bottom left - O(N)
  
    sort in polar coordinates order - O(NlogN)
  
    stack process - O(N)
  

  
Divide & Conquer: O(NlogN)
    
    sort in x - O(NlogN)
    
    recursion - T(N) = T(2/N) + O(N)
