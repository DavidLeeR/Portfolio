//Name: David Ramirez
//Date: 7/30/17
//Description: This is a script that uses express to create a dynamic html
//		page that displays GET or POST parameters. 

var express = require('express');
var mysql = require('./sql.js');

var app = express();
var handlebars = require('express-handlebars').create({defaultLayout:'main'});

app.use(express.static('public'));

app.engine('handlebars',handlebars.engine);
app.set('view engine', 'handlebars');
app.set('port', 3286);

//home page
app.get('/',function(req, res,next) {
	var context = {};
	mysql.pool.query('SELECT * FROM workouts', function(err, rows, fields){
		if(err){
			next(err);
			return;
		}
		
		//if there is data in the rows	
		if (rows.length > 0 && rows != null){

			var tableData = [];

			//put sql table data into variable
			for (var i = 0; i < rows.length; i++) {	
			
				tableData.push({
			
				'id': rows[i].id,
				'name': rows[i].name,
				'reps': rows[i].reps,
				'weight': rows[i].weight,
				'date': rows[i].date,
				'lbs': rows[i].lbs	
				});

				context.data = tableData;
			}
			
		}
		res.render('home',context);

	});
});


//insert into sql function (reference: lecture video)
app.get('/insert',function(req,res,next){
  var context = {};
  mysql.pool.query("INSERT INTO workouts (`name`, `reps`, `weight`, `date`, `lbs`) VALUES (?,?,?,?,?)", [req.query.name, req.query.reps, req.query.weight, req.query.date, req.query.lbs], function(err, result){
    if(err){
      next(err);
      return;
    }
    res.send({ recordId: result.insertId });
  });
});


//delete from sql function (reference: lecture video)
app.get('/delete', function(req,res,next){
	var context = {};
	mysql.pool.query("DELETE FROM workouts WHERE id=?", [req.query.id], function(err, result) {
		if(err){
			next(err);
			return;
		}
		context.results = "Deleted " + result.changedRows + " rows.";
		res.render('home',context);
	});
});


//edit sql row function
app.get('/edit', function (req, res, next) {
	var context = {};
	mysql.pool.query('SELECT * FROM workouts WHERE id=?', [req.query.id], function (err, rows, fields) {
	if (err) {
		next(err);
	return;
	}
        //if there is data in the row
	if (rows.length > 0 && rows != null){

	var tableData = [];

	for (var i = 0; i < rows.length; i++) {	
			
		tableData.push({
			
		'id': rows[i].id,
		'name': rows[i].name,
		'reps': rows[i].reps,
		'weight': rows[i].weight,
		'date': rows[i].date,
		'lbs': rows[i].lbs	
		});

		context.data = tableData;
	}
			
    }
    res.render('edit', context);
  });
});


//update sql function (reference: lecture video)
app.get('/update',function(req,res,next){
	var context = {};
	mysql.pool.query("SELECT * FROM workouts WHERE id=?", [req.query.id], function(err, result){
	if(err){
		next(err);
		return;
	}
	if(result.length == 1){
		var curVals = result[0];
      		mysql.pool.query("UPDATE workouts SET name=?, date=?, reps=?, weight=?, lbs=? WHERE id=? ",
        	[req.query.name || curVals.name, req.query.date || curVals.date, req.query.reps || curVals.reps, req.query.weight || curVals.weight,  req.query.lbs || curVals.lbs, req.query.id],function(err, result){
	if(err){
        	next(err);
        	return;
        }
        res.send();
      });
    }
  });
});

//reset table function (reference: assignment instructions)
app.get('/reset-table',function(req,res,next){
	var context = {};
	mysql.pool.query("DROP TABLE IF EXISTS workouts", function(err){ 
	var createString = "CREATE TABLE workouts("+
    			"id INT PRIMARY KEY AUTO_INCREMENT,"+
    			"name VARCHAR(255) NOT NULL,"+
    			"reps INT,"+
    			"weight INT,"+
    			"date DATE,"+
    			"lbs BOOLEAN)";
	mysql.pool.query(createString, function(err){
	context.results = "Table reset";
	res.render('home',context);
    })
  });
});


app.listen(app.get('port'), function(){
	console.log('Express started on http://localhost:' + app.get('port') + '; press Ctrl-C to terminate.');
}); 
