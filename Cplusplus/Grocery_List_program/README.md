**Grocery List program for Intro to Computer Science II at Oregon State University**

**Decription:** Program to create a detailed user defined grocery list. 

**Steps to compile and run program:**                                                   
Requires g++ (GNU) compiler version 4.8.5                                                            
1) Download this directory (Grocery_List_program)                                      
2) navigate to Grocery_List_program directory with command line                                
3) enter the command **make grocery** to compile the program                                 
4) enter the command **./grocery** to run the program                                       

**Demonstrates:** Operator overloading, designing with classes

**Requirements:** In this project, you need to design, implement, and test a grocery shopping list program.  The program should maintain and display a list of items.

You will design an Item class. The class should have data elements for the following information: item name, unit (i.e. can, box, pound, or ounce), quantity to buy (integer), and unit price (you can assume it is integer, but think about how to validate a float number). Consider following things: do you need any functions other than the constructor? How do you calculate the extended price for the item (quantity to buy times unit price)? How do you print it to the screen?

You will also need a List class. You will store Item objects in your List object. When you enter a new item, an Item object must be created and added to the List object. Use a dynamic array to hold the Item objects. The dynamic array should start with a capacity of 4 Item objects. That means the list should have the capability to have four items (array size of 4)with no item in it to start out with. Then, when you add a 5th item, the array should resize to create room for more items. Do you need a print function in this class? Think about it. Vectors are not allowed to use in this project.

Your program must perform the following activities: create a list, add items, remove items, and display the shopping list. To add an item, you should prompt the user to enter the name, unit, quantity to buy, and the unit price. To remove an item, ideally, your program should be able to find the exact item you need to delete by searching the item name, delete that item, and shift all the rest items up.  Alternatively, you can just delete the last item on the list.  That is acceptable as well. The display should show each item name in the list, item unit, the quantity to buy, the unit price, the extended price for each item, and the total price for all items. Oregon doesnâ€™t have a sales tax so you can ignore that. Use input validations for all the input. 

Once you have the List and Item classes working correctly, test if an item is already in your List before adding it. Overload the == operator to perform the test. There is a simple example to overload this operator in the book. Keep it simple. How will you compare items?  You can assume that the user will type the information correctly and compare them using the item names. If the item user wants to add is already on the list, print a message like â€œItem is already in the list, do you want to update it?â€ If the user chooses to update, replace the item information with the new one and if not, do nothing and back to the menu.

You should also test your program to make sure it works properly.  You do NOT need to test for every possible item in a grocery store, just a reasonable number.  How do you handle spaces in names? Are the extended prices calculated correctly? Is the total amount correct?  Also, remember to properly deallocate all dynamic memory and test the memory leaks on the flip.
