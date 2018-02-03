var mysql = require('mysql');
var pool = mysql.createPool({
  connectionLimit : 10,
  host            : 'classmysql.engr.oregonstate.edu',
  user            : 'cs290_ramirdav',
  password        : '5930',
  database        : 'cs290_ramirdav'
});

module.exports.pool = pool;

