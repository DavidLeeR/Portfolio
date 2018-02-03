
document.addEventListener('DOMContentLoaded', bindButtons);
function bindButtons() {
	document.getElementById('send').addEventListener('click', function (event) {
		var newExer = getForm();
		var checked = validation(newExer);
		if (checked == 1) {
			var req = new XMLHttpRequest();
			var name = newExer.name;
			var reps = newExer.reps;
			var weight = newExer.weight;
			var date = newExer.date;
			var lbs = newExer.lbs;

			req.open('GET', "/insert?"+"name="+name+"&reps="+reps+"&weight="+weight+"&date="+date+"&lbs="+lbs, true);
            	req.addEventListener('load', function () {
                if (req.status >= 200 && req.status < 400) {
                
			var response = JSON.parse(req.responseText);	
			var exer = getForm();
    			exer.id = response.recordId;
    			var tableBody = document.getElementById("tableBody");
    			var tableRow = document.createElement("tr");

    			var newName = document.createElement("td");
    			newName.textContent = exer.name;
    			tableRow.appendChild(newName);

    			var newReps = document.createElement("td");
    			newReps.textContent = exer.reps;
    			tableRow.appendChild(newReps);

    			var newWeight = document.createElement("td");
    			newWeight.textContent = exer.weight;
    			tableRow.appendChild(newWeight);

    			var newDate = document.createElement("td");
    			newDate.textContent = exer.date;
    			tableRow.appendChild(newDate);

    			var newLbs = document.createElement("td");
    			newLbs.textContent = exer.lbs;
    			tableRow.appendChild(newLbs);

    			tableBody.appendChild(tableRow);
    			addButton(tableRow, response.recordId);

                }
                else {
			console.log("Error in network request: " + req.statusText);
                }
            });

            req.send();
        }

        event.preventDefault();
    })
}



//function to remove sql row
function remove(element, ID) {
	var req = new XMLHttpRequest();
    	req.open('GET', "/delete?id="+ID, true);

	req.addEventListener('load', function () {
        	if (req.status >= 200 && req.status < 400) {
            		var response = req.responseText;
            		removeRow(element);
       		}
        	else {
            		console.log("Error in network request: " + req.statusText);
        }
    });

    req.send();
    event.preventDefault();
}


//function to addButton to inserted row
function addButton(addTo, insertedID) {
	var thisCell = document.createElement("td");
	var thisButton = document.createElement("button");
	thisButton.textContent = "Edit";

	(function (id) {
	
		thisButton.onclick = function () {
		edit(id);
        	}

	})(insertedID);

	thisCell.appendChild(thisButton);
	addTo.appendChild(thisCell);

	var removeCell = document.createElement("td");
	var removeButton = document.createElement("button");

	removeButton.textContent = "Delete";
	(function (button, id) {

		removeButton.onclick = function () {
		remove(button, id);
       		 }

    	})(removeButton, insertedID);

	removeCell.appendChild(removeButton);
	addTo.appendChild(removeCell);
}

//function to make sure valid entry
function validation(exer) {
	if (exer.name!=null&&exer!=null&&exer.name.length > 0) {
	return 1;
	}

	return 0;
}

// functionto open edit url
function edit(ID) {
	window.open(window.location.href + "edit?id="+ID, "_self");    
}

// function to remove a row from the dsiplayed table
function removeRow(button) {

	var targetRow = button.parentNode.parentNode;
	var body = targetRow.parentNode;
	
	body.removeChild(targetRow);
}

//function to read user input from form
function getForm() {

	var name = document.getElementById('name').value;
	var reps = document.getElementById('reps').value;
	var weight =document.getElementById('weight').value;
	var date = document.getElementById('date').value;
	var lbs = document.getElementById('lbs').checked;

	if (lbs== true){
		lbs =1;
	}
	
	else if (lbs== false) {
		lbs=0;
	}

	var exer = { "name": name, "reps": reps, "weight": weight, "date": date, "lbs": lbs };

	return exer;
}

