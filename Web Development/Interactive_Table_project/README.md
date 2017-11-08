**Project 3 for Web Development at Oregon State University.**

**Languages used:** JavaScript, HTML5

**Steps to run page:**
1) download this directory (interactive_table_project)                                                 
2) open the index.html file with a browser

**Demonstrates:** interacting with DOM, populating HTML page with java script, using java script to interact with HTML page

**Assignment description:** For this assignment you should submit a single zip file that contains the following two files:

    index.html
    script.js

index.html should be a skeleton HTML page. So it should have the following tags:

    doctype
    html
    head
    meta
    title
    body
    script

If you were to open index.html without including the associated JavaScript it should be entirely blank.

You should then use JavaScript to create all of the content of this page and append it to the body of the page. That content should include:

    A 4x4 table
        The top row should be a header row with header cells
        The 4 header cells, from left to right should say "Header 1", "Header 2" ... "Header 4
        The non header cells should contain their position. The upper left cell should contain the text "1, 1", the cell to its right "2, 1", the cell below it "1, 2" and so on.
    4 directional buttons (up, down, left right)
    A button labeled "Mark Cell"

When the page is loaded the upper left, non-header cell of the table should be 'selected'. This is denoted by it having a thicker border than the other cells. If you push the directional buttons other cells should be selected instead. So if you press the right button, cell 1,1 should no longer be selected and 2,1 should be selected instead.

If you are already on the top row and hit 'up' nothing should happen (you should not be able to move into the header cells). Likewise if you are all the way right and hit right or all the way at the bottom and hit down.

Hitting the "Mark Cell" button should permanently change the background of the selected cell to yellow. This should persist even after other cells are selected or marked.

Suggestion: If you are having a lot of trouble getting the page populated the way you want using JavaScript, just manually make the HTML so that you can continue to work on the rest of the assignment involving selecting and marking cells.

Note: When generating content for the page you will not get credit for simply using the innerHTML property of the body element to parse a string of HTML content. The purpose is to use the process of creating and appending element nodes to the document.
