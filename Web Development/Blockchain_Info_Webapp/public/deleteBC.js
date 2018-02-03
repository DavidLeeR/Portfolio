function deleteBC(bname, cname){

$.ajax({
        url: '/consensus/'+cname,
        type: 'DELETE',
        success: function(result){
                window.location.reload(true);
                }
        })
};


