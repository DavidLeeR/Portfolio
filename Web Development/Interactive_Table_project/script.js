//Name: David Ramirez
//Date: 7/23/17
//Description: This is a script that creates a table for an 
//              HTML document (index.html). It also creates 
//              buttons with functionality for navigating the
//              table as well as highlighting cells of the table. 

//create main table elements
var addTable = document.createElement("table");
var headers = document.createElement("thead");
var headRow = document.createElement("tr");
var data = document.createElement("tbody");

//create the header cells (4 total) and append them to header row
for (var a = 1; a <= 4; a++) {
    var headCell = document.createElement("th");
    headCell.textContent = "Header " + a;
    headRow.appendChild(headCell);
}

//create data rows (3 in total)
for (var b = 1; b <= 3; b++) {
    var dataRow = document.createElement("tr");

    //create data cells for each row (4 cells per row)
    for (var c = 1; c <= 4; c++) {
        var dataCell = document.createElement("td");
        dataCell.id = b.toString() + c.toString();
        dataCell.textContent = c + ", " + b;
        dataRow.appendChild(dataCell);
    }

    data.appendChild(dataRow);
}



//place all remaining unplaced elements in their respective locations
headers.appendChild(headRow);
addTable.appendChild(headers);
addTable.appendChild(data);
document.body.appendChild(addTable);

//create border for table
addTable.setAttribute("border", "1");

//create button elements and add to body
var up = document.createElement("button");
var down = document.createElement("button");
var left = document.createElement("button");
var right = document.createElement("button");
var markCell = document.createElement("button");

up.textContent = "Up";
down.textContent = "Down";
left.textContent = "Left";
right.textContent = "Right";
markCell.textContent = "Mark Cell";

document.body.appendChild(up);
document.body.appendChild(down);
document.body.appendChild(left);
document.body.appendChild(right);

//separate the markCell button from the directional buttons
document.body.appendChild(document.createElement("div"));
document.body.appendChild(markCell);

//create variable to hold the selected cell, set it to the
//first data cell 
var selectCell = document.getElementById("11");

//selectCell gets highlighted when DOM loads
document.addEventListener("DOMContentLoaded", function (event) {
    selectCell.style.border = "4px solid";
})

//functionality for the up button
up.addEventListener("click", function (event) {
    if (selectCell.id != 11 &&
        selectCell.id != 12 &&
        selectCell.id != 13 &&
        selectCell.id != 14)
    {
        var idNum = (parseInt(selectCell.id) - 10);

        selectCell.style.border = "1px solid";

        selectCell = document.getElementById(idNum.toString());

        selectCell.style.border = "4px solid";
    }
})

//functionality for the down button
down.addEventListener("click", function (event) {
    if (selectCell.id != 31 &&
        selectCell.id != 32 &&
        selectCell.id != 33 &&
        selectCell.id != 34) {
        var idNum = (parseInt(selectCell.id) + 10);

        selectCell.style.border = "1px solid";

        selectCell = document.getElementById(idNum.toString());

        selectCell.style.border = "4px solid";
    }
})

//functionality for the left button
left.addEventListener("click", function (event) {
    if (selectCell.id != 11 &&
        selectCell.id != 21 &&
        selectCell.id != 31)
    {
        var idNum = (parseInt(selectCell.id) - 1);

        selectCell.style.border = "1px solid";

        selectCell = document.getElementById(idNum.toString());

        selectCell.style.border = "4px solid";
    }
})

//functionality for the right button
right.addEventListener("click", function (event) {
    if (selectCell.id != 14 &&
        selectCell.id != 24 &&
        selectCell.id != 34) {
        var idNum = (parseInt(selectCell.id) + 1);

        selectCell.style.border = "1px solid";

        selectCell = document.getElementById(idNum.toString());

        selectCell.style.border = "4px solid";
    }
})

//functionality for the markCell button
markCell.addEventListener("click", function (event) {
    selectCell.style.backgroundColor = "yellow";
})

