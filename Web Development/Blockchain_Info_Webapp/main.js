/*  
    Uses express, dbcon for database connection, body parser to parse form data 
    handlebars for HTML templates  
*/

var express = require('express');
var mysql = require('./dbcon.js');
var bodyParser = require('body-parser');

var app = express();
var handlebars = require('express-handlebars').create({defaultLayout:'main'});

app.engine('handlebars', handlebars.engine);
app.use(bodyParser.urlencoded({extended:true}));
app.use(express.static('public'));
app.set('view engine', 'handlebars');
app.set('port', process.argv[2]);
app.set('mysql', mysql);

//app.use('/people', require('./people.js'));


//home page
app.get('/', function(req, res, next){
	var nameContext = {};
	mysql.pool.query('SELECT name FROM `blockchain_tbl`', function(err, rows, fields){
		if(err){
			next(err);
			return;
		}
		
		var nameData = [];

		//put sql table data into variable
		for (var i = 0; i < rows.length; i++){
			nameData.push({
				'name': rows[i].name
			});

			nameContext.data = nameData;
		}

		res.render('home', nameContext);
	});
});

//delete cons algo - blockchain relationship
app.delete('/consensus/:cname', function(req, res){
	console.log("here");
        var sql8 = "DELETE FROM ca_bc_tbl WHERE cabc_algoname='?'";
        var inserts8 = [req.params.cname];
        sql8 = mysql.pool.query(sql8, inserts8, function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.status(400);
                res.end();
            }else{
                res.status(202).end();
            }
        })
})

app.post('/consensus_delete', function (req,res){
	var sql5 = "DELETE FROM ca_bc_tbl WHERE cabc_algoname =? AND cabc_bcname=?";
        var inserts5 = [req.body.cnameE, req.body.bcrelE];
        sql5 = mysql.pool.query(sql5,inserts5,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.redirect('/consensus');
                 }
            });
});
                                    
//add consensus algo

app.post('/consensus_add', function(req,res){
        var sql5 = "INSERT INTO cons_algo_tbl (name, sec_score, ee_score) VALUES (?,?,?)";
        var inserts5 = [req.body.cname, req.body.sscore, req.body.eescore];
        sql5 = mysql.pool.query(sql5,inserts5,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
                //res.redirect('/consensus');
            }
        });

	var sql6 = "INSERT INTO ca_bc_tbl (cabc_algoname, cabc_bcname) VALUES (?,?)";
        var inserts6 = [req.body.cname, req.body.bcrel];
	if (req.body.bcrel != "NULL")
	{
        sql6 = mysql.pool.query(sql6,inserts6,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.redirect('/consensus');
            }
        });
	}
	else{
		res.redirect('/consensus');
	}
});

app.post('/consensus_edit', function(req,res){
	var sql9 = "UPDATE cons_algo_tbl SET name = ?, sec_score = ?, ee_score =? WHERE name =?";
	var inserts9 = [req.body.cnameE, req.body.sscoreE, req.body.eescoreE, req.body.ccnameE]
	sql9 = mysql.pool.query(sql9, inserts9, function(error, results, fields){
		if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
//                res.redirect('/consensus');
                 }
        });

	var sql10 = "UPDATE ca_bc_tbl SET cabc_algoname = ?, cabc_bcname = ?  WHERE cabc_algoname =?";
        var inserts10 = [req.body.cnameE, req.body.bcrelE, req.body.ccnameE]
        sql10 = mysql.pool.query(sql10, inserts10, function(error, results, fields){
                if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.redirect('/consensus');
                 }
        });

                
});



//consensus algorithms info page
app.get('/consensus', function(req, res, next){
	var algoContext = {};
	algoContext.jsscripts =["deleteBC.js"];
	mysql.pool.query('SELECT * FROM `cons_algo_tbl`', function(err, rows, fields){
		if(err){
			next(err);
			return;
		}
		
		var algoData =[];

		//put sql table data into variable
		for (var i = 0; i < rows.length; i++){
			algoData.push({
				'name': rows[i].name,
				'sec_score': rows[i].sec_score,
				'ee_score': rows[i].ee_score
			});

			algoContext.data = algoData;
		}

	//	res.render('consensus', algoContext);
	});
	mysql.pool.query('SELECT cabc_algoname AS cname, cabc_bcname AS bname FROM `ca_bc_tbl` ', function(err, rows, fields){
		if(err){
			next(err);
			return;
		}
		
		var algorelData =[];

		//put sql table data into variable
		for (var i = 0; i < rows.length; i++){
			algorelData.push({
				'cname': rows[i].cname,
				'bname': rows[i].bname,
			});

			algoContext.ba = algorelData;
		}

		res.render('consensus', algoContext);
	});
});

//add a node to the ethereum page

app.post('/Ethereum_add_node', function(req,res){
        var sql3 = "INSERT INTO node_tbl (net_address, blockchain, os) VALUES (?,?,?)";
        var inserts3 = [req.body.ipaddress, "Ethereum", req.body.os];
        sql3 = mysql.pool.query(sql3,inserts3,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.redirect('/Ethereum');
            }
        });
    });



//add an account to the ethereum page

app.post('/Ethereum_add_account', function(req,res){
        var sql = "INSERT INTO account_tbl (bc_address, bc, crypto_amount) VALUES (?,?,?)";
        var inserts = [req.body.bcaddress, "Ethereum", req.body.amount];
        sql = mysql.pool.query(sql,inserts,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.redirect('/Ethereum');
            }
        });
});

//add a user to the ethereum page

app.post('/Ethereum_add_user', function(req,res){
        var sql = "INSERT INTO people_tbl (ssn, use_reason, f_name, l_name) VALUES (?,?,?,?)";
        var inserts = [req.body.ssnf,req.body.usef, req.body.fnamef, req.body.lnamef];
        sql = mysql.pool.query(sql,inserts,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
        //        res.redirect('/Bitcoin');
            }
        });

	var sql2 = "INSERT INTO node_people_tbl (node_address, people_ssn) VALUES (?,?)";
	var inserts2 = [req.body.addressf, req.body.ssnf];
	
	sql2 = mysql.pool.query(sql2,inserts2,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.redirect('/Ethereum');
            }
        });
 
});



//Ethereum page
app.get('/Ethereum', function(req, res, next){
	var bitcoinContext = {};
	mysql.pool.query('SELECT * FROM `blockchain_tbl` WHERE name = "Ethereum"', function(err, rows, fields){
		if (err){
			next(err);
			return;
		}

		var bitcoinData = [];

		//put sql table data into variable
		bitcoinData.push({
			'name': "Ethereum",
			'crypto': rows[0].crypto,
			'b_time': rows[0].b_time,
			'b_size': rows[0].b_size
		});

		bitcoinContext.data = bitcoinData;

		//res.render('bitcoin',bitcoinContext);
	});

	mysql.pool.query('SELECT * FROM `node_tbl` WHERE blockchain = "Ethereum"', function(err, rows, fields){
		if (err){
			next(err);
			return;
		}

		var nodeData = [];

		//put sql table data into variable
		for (var i = 0; i < rows.length; i++){

			nodeData.push({
				'address': rows[i].net_address,
				'os': rows[i].os
			});
		}

		bitcoinContext.node = nodeData;

	//	res.render('bitcoin',bitcoinContext);	
	});

	//res.render('bitcoin',bitcoinContext);
	


	mysql.pool.query('SELECT p.f_name, p.l_name, p.use_reason, n.net_address FROM `people_tbl` p INNER JOIN `node_people_tbl` np ON np.people_ssn = p.ssn INNER JOIN `node_tbl` n ON n.net_address = np.node_address WHERE n.blockchain = "Ethereum"', function(err, rows, fields){
		if (err){
			next(err);
			return;
		}

		var userData = [];

		//put sql table data into variable
		for (var i = 0; i < rows.length; i++){
			userData.push({
				'fname': rows[i].f_name,
				'lname': rows[i].l_name,
				'use': rows[i].use_reason,
				'address': rows[i].net_address 
			});
		}
	
		bitcoinContext.user = userData;

	//	res.render('bitcoin', bitcoinContext);
	});

	mysql.pool.query('SELECT net_address FROM `node_tbl` WHERE blockchain = "Ethereum"', function(err, rows, fields){
		if (err){
			next(err);
			return;
		}

		var addressData = [];

		//put sql table data into variable
		for (var i = 0; i < rows.length; i++){
			addressData.push({
				'addy': rows[i].net_address
			});
		
		bitcoinContext.nAddress = addressData;

		}

		//res.render('bitcoin', bitcoinContext);
	}); 

	mysql.pool.query('SELECT bc_address, crypto_amount FROM `account_tbl` WHERE bc = "Ethereum"', function(err, rows, fields){
		if (err){
			next(err);
			return;
		}

		var accountData = [];

		//put sql table data into variable
		for (var i = 0; i < rows.length; i++){
			accountData.push({
				'addy': rows[i].bc_address,
				'amount': rows[i].crypto_amount
			});
		
		bitcoinContext.account = accountData;

		}

		res.render('ethereum', bitcoinContext);
	}); 
});


//add a node to the Decred page

app.post('/Decred_add_node', function(req,res){
        var sql3 = "INSERT INTO node_tbl (net_address, blockchain, os) VALUES (?,?,?)";
        var inserts3 = [req.body.ipaddress, "Decred", req.body.os];
        sql3 = mysql.pool.query(sql3,inserts3,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.redirect('/Decred');
            }
        });
    });



//add an account to the decred page

app.post('/Decred_add_account', function(req,res){
        var sql = "INSERT INTO account_tbl (bc_address, bc, crypto_amount) VALUES (?,?,?)";
        var inserts = [req.body.bcaddress, "Decred", req.body.amount];
        sql = mysql.pool.query(sql,inserts,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.redirect('/Decred');
            }
        });
});

//add a user to the decred page

app.post('/Decred_add_user', function(req,res){
        var sql = "INSERT INTO people_tbl (ssn, use_reason, f_name, l_name) VALUES (?,?,?,?)";
        var inserts = [req.body.ssnf,req.body.usef, req.body.fnamef, req.body.lnamef];
        sql = mysql.pool.query(sql,inserts,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
        //        res.redirect('/Bitcoin');
            }
        });

	var sql2 = "INSERT INTO node_people_tbl (node_address, people_ssn) VALUES (?,?)";
	var inserts2 = [req.body.addressf, req.body.ssnf];
	
	sql2 = mysql.pool.query(sql2,inserts2,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.redirect('/Decred');
            }
        });
 
});



//Decred page
app.get('/Decred', function(req, res, next){
	var bitcoinContext = {};
	mysql.pool.query('SELECT * FROM `blockchain_tbl` WHERE name = "Decred"', function(err, rows, fields){
		if (err){
			next(err);
			return;
		}

		var bitcoinData = [];

		//put sql table data into variable
		bitcoinData.push({
			'name': "Decred",
			'crypto': rows[0].crypto,
			'b_time': rows[0].b_time,
			'b_size': rows[0].b_size
		});

		bitcoinContext.data = bitcoinData;

		//res.render('bitcoin',bitcoinContext);
	});

	mysql.pool.query('SELECT * FROM `node_tbl` WHERE blockchain = "Decred"', function(err, rows, fields){
		if (err){
			next(err);
			return;
		}

		var nodeData = [];

		//put sql table data into variable
		for (var i = 0; i < rows.length; i++){

			nodeData.push({
				'address': rows[i].net_address,
				'os': rows[i].os
			});
		}

		bitcoinContext.node = nodeData;

	//	res.render('bitcoin',bitcoinContext);	
	});

	//res.render('bitcoin',bitcoinContext);
	


	mysql.pool.query('SELECT p.f_name, p.l_name, p.use_reason, n.net_address FROM `people_tbl` p INNER JOIN `node_people_tbl` np ON np.people_ssn = p.ssn INNER JOIN `node_tbl` n ON n.net_address = np.node_address WHERE n.blockchain = "Decred"', function(err, rows, fields){
		if (err){
			next(err);
			return;
		}

		var userData = [];

		//put sql table data into variable
		for (var i = 0; i < rows.length; i++){
			userData.push({
				'fname': rows[i].f_name,
				'lname': rows[i].l_name,
				'use': rows[i].use_reason,
				'address': rows[i].net_address 
			});
		}
	
		bitcoinContext.user = userData;

	//	res.render('bitcoin', bitcoinContext);
	});

	mysql.pool.query('SELECT net_address FROM `node_tbl` WHERE blockchain = "Decred"', function(err, rows, fields){
		if (err){
			next(err);
			return;
		}

		var addressData = [];

		//put sql table data into variable
		for (var i = 0; i < rows.length; i++){
			addressData.push({
				'addy': rows[i].net_address
			});
		
		bitcoinContext.nAddress = addressData;

		}

		//res.render('bitcoin', bitcoinContext);
	}); 

	mysql.pool.query('SELECT bc_address, crypto_amount FROM `account_tbl` WHERE bc = "Decred"', function(err, rows, fields){
		if (err){
			next(err);
			return;
		}

		var accountData = [];

		//put sql table data into variable
		for (var i = 0; i < rows.length; i++){
			accountData.push({
				'addy': rows[i].bc_address,
				'amount': rows[i].crypto_amount
			});
		
		bitcoinContext.account = accountData;

		}

		res.render('decred', bitcoinContext);
	}); 
});

//add a node to the NXT page

app.post('/NXT_add_node', function(req,res){
        var sql3 = "INSERT INTO node_tbl (net_address, blockchain, os) VALUES (?,?,?)";
        var inserts3 = [req.body.ipaddress, "NXT", req.body.os];
        sql3 = mysql.pool.query(sql3,inserts3,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.redirect('/NXT');
            }
        });
    });



//add an account to the NXT page

app.post('/NXT_add_account', function(req,res){
        var sql = "INSERT INTO account_tbl (bc_address, bc, crypto_amount) VALUES (?,?,?)";
        var inserts = [req.body.bcaddress, "NXT", req.body.amount];
        sql = mysql.pool.query(sql,inserts,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.redirect('/NXT');
            }
        });
});

//add a user to the NXT page

app.post('/NXT_add_user', function(req,res){
        var sql = "INSERT INTO people_tbl (ssn, use_reason, f_name, l_name) VALUES (?,?,?,?)";
        var inserts = [req.body.ssnf,req.body.usef, req.body.fnamef, req.body.lnamef];
        sql = mysql.pool.query(sql,inserts,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
        //        res.redirect('/Bitcoin');
            }
        });

	var sql2 = "INSERT INTO node_people_tbl (node_address, people_ssn) VALUES (?,?)";
	var inserts2 = [req.body.addressf, req.body.ssnf];
	
	sql2 = mysql.pool.query(sql2,inserts2,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.redirect('/NXT');
            }
        });
 
});



//NXT page
app.get('/NXT', function(req, res, next){
	var bitcoinContext = {};
	mysql.pool.query('SELECT * FROM `blockchain_tbl` WHERE name = "NXT"', function(err, rows, fields){
		if (err){
			next(err);
			return;
		}

		var bitcoinData = [];

		//put sql table data into variable
		bitcoinData.push({
			'name': "NXT",
			'crypto': rows[0].crypto,
			'b_time': rows[0].b_time,
			'b_size': rows[0].b_size
		});

		bitcoinContext.data = bitcoinData;

		//res.render('bitcoin',bitcoinContext);
	});

	mysql.pool.query('SELECT * FROM `node_tbl` WHERE blockchain = "NXT"', function(err, rows, fields){
		if (err){
			next(err);
			return;
		}

		var nodeData = [];

		//put sql table data into variable
		for (var i = 0; i < rows.length; i++){

			nodeData.push({
				'address': rows[i].net_address,
				'os': rows[i].os
			});
		}

		bitcoinContext.node = nodeData;

	//	res.render('bitcoin',bitcoinContext);	
	});

	//res.render('bitcoin',bitcoinContext);
	


	mysql.pool.query('SELECT p.f_name, p.l_name, p.use_reason, n.net_address FROM `people_tbl` p INNER JOIN `node_people_tbl` np ON np.people_ssn = p.ssn INNER JOIN `node_tbl` n ON n.net_address = np.node_address WHERE n.blockchain = "NXT"', function(err, rows, fields){
		if (err){
			next(err);
			return;
		}

		var userData = [];

		//put sql table data into variable
		for (var i = 0; i < rows.length; i++){
			userData.push({
				'fname': rows[i].f_name,
				'lname': rows[i].l_name,
				'use': rows[i].use_reason,
				'address': rows[i].net_address 
			});
		}
	
		bitcoinContext.user = userData;

	//	res.render('bitcoin', bitcoinContext);
	});

	mysql.pool.query('SELECT net_address FROM `node_tbl` WHERE blockchain = "NXT"', function(err, rows, fields){
		if (err){
			next(err);
			return;
		}

		var addressData = [];

		//put sql table data into variable
		for (var i = 0; i < rows.length; i++){
			addressData.push({
				'addy': rows[i].net_address
			});
		
		bitcoinContext.nAddress = addressData;

		}

		//res.render('bitcoin', bitcoinContext);
	}); 

	mysql.pool.query('SELECT bc_address, crypto_amount FROM `account_tbl` WHERE bc = "NXT"', function(err, rows, fields){
		if (err){
			next(err);
			return;
		}

		var accountData = [];

		//put sql table data into variable
		for (var i = 0; i < rows.length; i++){
			accountData.push({
				'addy': rows[i].bc_address,
				'amount': rows[i].crypto_amount
			});
		
		bitcoinContext.account = accountData;

		}

		res.render('NXT', bitcoinContext);
	}); 
});


//add a node to the Slimcoin page

app.post('/Slimcoin_add_node', function(req,res){
        var sql3 = "INSERT INTO node_tbl (net_address, blockchain, os) VALUES (?,?,?)";
        var inserts3 = [req.body.ipaddress, "Slimcoin", req.body.os];
        sql3 = mysql.pool.query(sql3,inserts3,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.redirect('/Slimcoin');
            }
        });
    });



//add an account to the bitcoin page

app.post('/Slimcoin_add_account', function(req,res){
        var sql = "INSERT INTO account_tbl (bc_address, bc, crypto_amount) VALUES (?,?,?)";
        var inserts = [req.body.bcaddress, "Slimcoin", req.body.amount];
        sql = mysql.pool.query(sql,inserts,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.redirect('/Slimcoin');
            }
        });
});

//add a user to the bitcoin page

app.post('/Slimcoin_add_user', function(req,res){
        var sql = "INSERT INTO people_tbl (ssn, use_reason, f_name, l_name) VALUES (?,?,?,?)";
        var inserts = [req.body.ssnf,req.body.usef, req.body.fnamef, req.body.lnamef];
        sql = mysql.pool.query(sql,inserts,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
        //        res.redirect('/Bitcoin');
            }
        });

	var sql2 = "INSERT INTO node_people_tbl (node_address, people_ssn) VALUES (?,?)";
	var inserts2 = [req.body.addressf, req.body.ssnf];
	
	sql2 = mysql.pool.query(sql2,inserts2,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.redirect('/Slimcoin');
            }
        });
 
});



//Slimcoin page
app.get('/Slimcoin', function(req, res, next){
	var bitcoinContext = {};
	mysql.pool.query('SELECT * FROM `blockchain_tbl` WHERE name = "Slimcoin"', function(err, rows, fields){
		if (err){
			next(err);
			return;
		}

		var bitcoinData = [];

		//put sql table data into variable
		bitcoinData.push({
			'name': "Slimcoin",
			'crypto': rows[0].crypto,
			'b_time': rows[0].b_time,
			'b_size': rows[0].b_size
		});

		bitcoinContext.data = bitcoinData;

		//res.render('bitcoin',bitcoinContext);
	});

	mysql.pool.query('SELECT * FROM `node_tbl` WHERE blockchain = "Slimcoin"', function(err, rows, fields){
		if (err){
			next(err);
			return;
		}

		var nodeData = [];

		//put sql table data into variable
		for (var i = 0; i < rows.length; i++){

			nodeData.push({
				'address': rows[i].net_address,
				'os': rows[i].os
			});
		}

		bitcoinContext.node = nodeData;

	//	res.render('bitcoin',bitcoinContext);	
	});

	//res.render('bitcoin',bitcoinContext);
	


	mysql.pool.query('SELECT p.f_name, p.l_name, p.use_reason, n.net_address FROM `people_tbl` p INNER JOIN `node_people_tbl` np ON np.people_ssn = p.ssn INNER JOIN `node_tbl` n ON n.net_address = np.node_address WHERE n.blockchain = "Slimcoin"', function(err, rows, fields){
		if (err){
			next(err);
			return;
		}

		var userData = [];

		//put sql table data into variable
		for (var i = 0; i < rows.length; i++){
			userData.push({
				'fname': rows[i].f_name,
				'lname': rows[i].l_name,
				'use': rows[i].use_reason,
				'address': rows[i].net_address 
			});
		}
	
		bitcoinContext.user = userData;

	//	res.render('bitcoin', bitcoinContext);
	});

	mysql.pool.query('SELECT net_address FROM `node_tbl` WHERE blockchain = "Slimcoin"', function(err, rows, fields){
		if (err){
			next(err);
			return;
		}

		var addressData = [];

		//put sql table data into variable
		for (var i = 0; i < rows.length; i++){
			addressData.push({
				'addy': rows[i].net_address
			});
		
		bitcoinContext.nAddress = addressData;

		}

		//res.render('bitcoin', bitcoinContext);
	}); 

	mysql.pool.query('SELECT bc_address, crypto_amount FROM `account_tbl` WHERE bc = "Slimcoin"', function(err, rows, fields){
		if (err){
			next(err);
			return;
		}

		var accountData = [];

		//put sql table data into variable
		for (var i = 0; i < rows.length; i++){
			accountData.push({
				'addy': rows[i].bc_address,
				'amount': rows[i].crypto_amount
			});
		
		bitcoinContext.account = accountData;

		}

		res.render('slimcoin', bitcoinContext);
	}); 
});



//add a node to the Bitcoin page

app.post('/Bitcoin_add_node', function(req,res){
        var sql3 = "INSERT INTO node_tbl (net_address, blockchain, os) VALUES (?,?,?)";
        var inserts3 = [req.body.ipaddress, "Bitcoin", req.body.os];
        sql3 = mysql.pool.query(sql3,inserts3,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.redirect('/Bitcoin');
            }
        });
    });



//add an account to the bitcoin page

app.post('/Bitcoin_add_account', function(req,res){
        var sql = "INSERT INTO account_tbl (bc_address, bc, crypto_amount) VALUES (?,?,?)";
        var inserts = [req.body.bcaddress, "Bitcoin", req.body.amount];
        sql = mysql.pool.query(sql,inserts,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.redirect('/Bitcoin');
            }
        });
});

//add a user to the bitcoin page

app.post('/Bitcoin_add_user', function(req,res){
        var sql = "INSERT INTO people_tbl (ssn, use_reason, f_name, l_name) VALUES (?,?,?,?)";
        var inserts = [req.body.ssnf,req.body.usef, req.body.fnamef, req.body.lnamef];
        sql = mysql.pool.query(sql,inserts,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
        //        res.redirect('/Bitcoin');
            }
        });

	var sql2 = "INSERT INTO node_people_tbl (node_address, people_ssn) VALUES (?,?)";
	var inserts2 = [req.body.addressf, req.body.ssnf];
	
	sql2 = mysql.pool.query(sql2,inserts2,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.redirect('/Bitcoin');
            }
        });
 
});



//Bitcoin page
app.get('/Bitcoin', function(req, res, next){
	var bitcoinContext = {};
	mysql.pool.query('SELECT * FROM `blockchain_tbl` WHERE name = "Bitcoin"', function(err, rows, fields){
		if (err){
			next(err);
			return;
		}

		var bitcoinData = [];

		//put sql table data into variable
		bitcoinData.push({
			'name': "Bitcoin",
			'crypto': rows[0].crypto,
			'b_time': rows[0].b_time,
			'b_size': rows[0].b_size
		});

		bitcoinContext.data = bitcoinData;

		//res.render('bitcoin',bitcoinContext);
	});

	mysql.pool.query('SELECT * FROM `node_tbl` WHERE blockchain = "Bitcoin"', function(err, rows, fields){
		if (err){
			next(err);
			return;
		}

		var nodeData = [];

		//put sql table data into variable
		for (var i = 0; i < rows.length; i++){

			nodeData.push({
				'address': rows[i].net_address,
				'os': rows[i].os
			});
		}

		bitcoinContext.node = nodeData;

	//	res.render('bitcoin',bitcoinContext);	
	});

	//res.render('bitcoin',bitcoinContext);
	


	mysql.pool.query('SELECT p.f_name, p.l_name, p.use_reason, n.net_address FROM `people_tbl` p INNER JOIN `node_people_tbl` np ON np.people_ssn = p.ssn INNER JOIN `node_tbl` n ON n.net_address = np.node_address WHERE n.blockchain = "Bitcoin"', function(err, rows, fields){
		if (err){
			next(err);
			return;
		}

		var userData = [];

		//put sql table data into variable
		for (var i = 0; i < rows.length; i++){
			userData.push({
				'fname': rows[i].f_name,
				'lname': rows[i].l_name,
				'use': rows[i].use_reason,
				'address': rows[i].net_address 
			});
		}
	
		bitcoinContext.user = userData;

	//	res.render('bitcoin', bitcoinContext);
	});

	mysql.pool.query('SELECT net_address FROM `node_tbl` WHERE blockchain = "Bitcoin"', function(err, rows, fields){
		if (err){
			next(err);
			return;
		}

		var addressData = [];

		//put sql table data into variable
		for (var i = 0; i < rows.length; i++){
			addressData.push({
				'addy': rows[i].net_address
			});
		
		bitcoinContext.nAddress = addressData;

		}

		//res.render('bitcoin', bitcoinContext);
	}); 

	mysql.pool.query('SELECT bc_address, crypto_amount FROM `account_tbl` WHERE bc = "Bitcoin"', function(err, rows, fields){
		if (err){
			next(err);
			return;
		}

		var accountData = [];

		//put sql table data into variable
		for (var i = 0; i < rows.length; i++){
			accountData.push({
				'addy': rows[i].bc_address,
				'amount': rows[i].crypto_amount
			});
		
		bitcoinContext.account = accountData;

		}

		res.render('bitcoin', bitcoinContext);
	}); 
});


app.use(function(req,res){
  res.status(404);
  res.render('404');
});

//error handler
app.use(function(err, req, res, next){
  console.error(err.stack);
  res.status(500);
  res.render('500');
});

app.listen(app.get('port'), function(){
  console.log('Express started on http://localhost:' + app.get('port') + '; press Ctrl-C to terminate.');
});
