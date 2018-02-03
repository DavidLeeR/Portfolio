var mysql = require('mysql');
var pool = mysql.createPool({
  connectionLimit : 10,
  host            : 'classmysql.engr.oregonstate.edu',
  user            : 'cs340_ramirdav',
  password        : '071591',
  database        : 'cs340_ramirdav'
});
module.exports.pool = pool;
