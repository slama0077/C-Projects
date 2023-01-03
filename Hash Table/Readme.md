This input for this project is a tab delimited text file containing a table in which each row is a person and each column represents an information
relevant to the person, such as id, first name, last name, state, city, and so on. This project uses the idea of hash mapping and uses one of the information such 
as state, city, or Postal code as a key to create a hash table. It uses both open addressing and quadratic probing as the collision resolution strategy. 
With the usage of hash mapping, the access to those data such as look up is possible in constant time which increases the run time efficiency. 

To run this program you must provide 3 command line arguments:

1) filename containing the data
2) table_size (prime preferred) 
3) key (one of the information of column such as state, city, postal code ...)

User can use 2 commands to output data:
1) print - prints all the indices of the hash table, mentioning the key value of each index and the number of persons stored in each index
2) lookup - to use this command, you need to provide the key value. This prints every person with that key value and prints out all information of the person in constant time.

This project uses custom linked-lists to complete the task. More explanation about code is done in the coding file (p4) itself. A testvector file is added, which can
be used in command line argument to test the code. 

