function Automobile(year, make, model, type) {
    this.year = year; //integer (ex. 2001, 1995)
    this.make = make; //string (ex. Honda, Ford)
    this.model = model; //string (ex. Accord, Focus)
    this.type = type; //string (ex. Pickup, SUV)
}

var automobiles = [
    new Automobile(1995, "Honda", "Accord", "Sedan"),
    new Automobile(1990, "Ford", "F-150", "Pickup"),
    new Automobile(2000, "GMC", "Tahoe", "SUV"),
    new Automobile(2010, "Toyota", "Tacoma", "Pickup"),
    new Automobile(2005, "Lotus", "Elise", "Roadster"),
    new Automobile(2008, "Subaru", "Outback", "Wagon")
];

Automobile.prototype.logMe = function (displayType) {

    if (displayType == true) {
        console.log(this.year + " " + this.make + " " + this.model + " " + this.type);
    }

    else if (displayType == false) {
        console.log(this.year + " " + this.make + " " + this.model);
    }
}

/*This function sorts arrays using an arbitrary comparator. You pass it a comparator and an array of objects appropriate for that comparator and it will return a new array which is sorted with the largest object in index 0 and the smallest in the last index*/
function sortArr(comparator, array) {

    /*your code here*/
    var sortedAutos = [];
    var sortedAutos = automobiles;
    var size = sortedAutos.length;

    //bubble sort
    for (size; size > 0; size--) {

        for (var n = 1; n < size; n++) {

            //if array[n-1]'s comparator value is less than that of array[n], switch them
            if (comparator(sortedAutos[n - 1], sortedAutos[n]) == false) {
                var temp = sortedAutos[n - 1];
                sortedAutos[n - 1] = sortedAutos[n];
                sortedAutos[n] = temp;
            }
        }
    }

    return sortedAutos;
}


/*A comparator takes two arguments and uses some algorithm to compare them. If the first argument is larger or greater than the 2nd it returns true, otherwise it returns false. Here is an example that works on integers*/
function exComparator(int1, int2) {
    if (int1 > int2) {
        return true;
    } else {
        return false;
    }
}

/*For all comparators if cars are 'tied' according to the comparison rules then the order of those 'tied' cars is not specified and either can come first*/

/*This compares two auto
mobiles based on their year. Newer cars are "greater" than older cars.*/
function yearComparator(auto1, auto2) {

    /* your code here*/
    if (auto1.year > auto2.year) {
        return true;
    }

    else {
        return false;
    }
}

/*This compares two automobiles based on their make. It should be case insensitive and makes which are alphabetically earlier in the alphabet are "greater" than ones that come later.*/
function makeComparator(auto1, auto2) {

    /* your code here*/
    //temp1 will hold the make of auto1 in all lower case
    var temp1 = (function (name) {
        var temp = name.toLowerCase();
        return temp;
    }(auto1.make));

    //temp2 will hold the make of auto2 in all lower case
    var temp2 = (function (name) {
        var temp = name.toLowerCase();
        return temp;
    }(auto2.make));

    //compare each letter of the makes for as long as 
    //the length of the shortest make 
    if (temp1.length >= temp2.length) {
        for (var i = 0; i < temp2.length; i++) {
            if (temp1[i] < temp2[i]) {
                return true;
            }
            else if (temp1[i] == temp2[i]) {
                //check next letter
            }
            else {
                return false;
            }
        }
    }

    //compare each letter of the makes for as long as 
    //the length of the shortest make
    else if (temp2.length > temp1.length) {
        for (var i = 0; i < temp1.length; i++) {
            if (temp1[i] < temp2[i]) {
                return true;
            }
            else if (temp1[i] == temp2[i]) {
                //check next letter
            }
            else {
                return false;
            }
        }
    }
}

//makeComparator(automobiles[5], automobiles[3]);

/*This compares two automobiles based on their type. The ordering from "greatest" to "least" is as follows: roadster, pickup, suv, wagon, (types not otherwise listed). It should be case insensitive. If two cars are of equal type then the newest one by model year should be considered "greater".*/
function typeComparator(auto1, auto2) {

    /* your code here*/
    //convert type (in all lower case) to value for auto1
    if (auto1.type.toLowerCase() == 'roadster') {
        var val1 = 5;
    }
    else if (auto1.type.toLowerCase() == 'pickup') {
        var val1 = 4;
    }
    else if (auto1.type.toLowerCase() == 'suv') {
        var val1 = 3;
    }
    else if (auto1.type.toLowerCase() == 'wagon') {
        var val1 = 2;
    }
    else {
        var val1 = 1;
    }

    //convert type (in all lower case) to value for auto2
    if (auto2.type.toLowerCase() == 'roadster') {
        var val2 = 5;
    }
    else if (auto2.type.toLowerCase() == 'pickup') {
        var val2 = 4;
    }
    else if (auto2.type.toLowerCase() == 'suv') {
        var val2 = 3;
    }
    else if (auto2.type.toLowerCase() == 'wagon') {
        var val2 = 2;
    }
    else {
        var val2 = 1;
    }

    if (val1 > val2) {
        return true;
    }

        //if the types are the same, compare year
    else if (val1 == val2) {
        return (yearComparator(auto1, auto2));
    }

    else {
        return false;
    }

}

console.log("*****");

//automobiles sorted by year
console.log("The cars sorted by year are:");
var yearSort = [];
var yearSort = sortArr(yearComparator, automobiles);

yearSort.forEach(function (automobile) {
    automobile.logMe(false);
})
console.log('');


//automobiles sorted by make
console.log("The cars sorted by make are:");
var makeSort = [];
var makeSort = sortArr(makeComparator, automobiles);

makeSort.forEach(function (automobile) {
    automobile.logMe(false);
})
console.log('');


//automobiles sorted by type
console.log("The cars sorted by type are:");
var typreSort = [];
var typreSort = sortArr(typeComparator, automobiles);

makeSort.forEach(function (automobile) {
    automobile.logMe(true);
})

console.log("*****");

/*Your program should output the following to the console.log, including the opening and closing 5 stars. All values in parenthesis should be replaced with appropriate values. Each line is a seperate call to console.log.

Each line representing a car should be produced via a logMe function. This function should be added to the Automobile class and accept a single boolean argument. If the argument is 'true' then it prints "year make model type" with the year, make, model and type being the values appropriate for the automobile. If the argument is 'false' then the type is ommited and just the "year make model" is logged.

*****
The cars sorted by year are:
(year make model of the 'greatest' car)
(...)
(year make model of the 'least' car)

The cars sorted by make are:
(year make model of the 'greatest' car)
(...)
(year make model of the 'least' car)

The cars sorted by type are:
(year make model type of the 'greatest' car)
(...)
(year make model type of the 'least' car)
*****

As an example of the content in the parenthesis:
1990 Ford F-150 */