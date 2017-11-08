document.addEventListener('DOMContentLoaded', bindButtons);
document.addEventListener('DOMContentLoaded', checkMetric);

function bindButtons() {

	document.getElementById('updateWorkout').addEventListener('click', function (event) {
       	var newExer = getForm();
        var isValid = validation(newExer);
        if (isValid) {
		var req = new XMLHttpRequest();
		var id = newExer.id;
    		var name = newExer.name;
    		var reps = newExer.reps;
    		var weight = newExer.weight;
    		var date = newExer.date;
    		var lbs = newExer.lbs;

    		var params = "id=" + id + "&name=" + name + "&reps=" + reps + "&weight=" + weight + "&date=" + date + "&lbs=" + lbs;
                
            	var url = "/update?" + params;
            	req.open('GET', url, true);
            	req.addEventListener('load', function () {

                if (req.status >= 200 && req.status < 400) {
                    var test = window.location.href.split("/edit")[0];
                    window.location.href = test;
                }

                else {
                    console.log("Error in network request: " + req.statusText);
                }
            });

            req.send();
            event.preventDefault();
        }
    })
}


function validation(exer) {

	if (exer != null && exer.name != null && exer.name.length > 0) {

        return true;
	}

   	return false;
}

function checkMetric() {

	var lbs = document.getElementById('lbs').value;
 	if (lbs == 1) {

        document.getElementById("lbs").checked = true;
    	}

    	else {

        document.getElementById("lbs").checked = false;
    	}
}

function getForm() {
	var id = document.getElementById('id').value;
	var name = document.getElementById('name').value;
	var reps = document.getElementById('reps').value;
	var weight = document.getElementById('weight').value;
	var date = document.getElementById('date').value;
	var lbs = document.getElementById('lbs').checked;
	if (lbs == true) {
        	lbs = 1;
    	}
    	else {
        	lbs = 0;
   	 }	

    	var exer = { "id": id, "name": name, "reps": reps, "weight": weight, "date": date, "lbs": lbs };
    	return exer;
}
