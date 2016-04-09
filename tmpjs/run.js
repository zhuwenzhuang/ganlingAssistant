
var exec = require('child_process').exec; 
var num = process.argv[2] || '';
var fs= require('fs') ;
var fname=num+'.txt';
var path='E:/QTWorkspace/tmpjs/';
if (num === '') {
    console.log('please input: node run.js (teacher num)');
} else {
	console.log('node '+path+'getKebiao.js '+num);

    if (!fs.existsSync(path+num)) {
       fs.mkdirSync(path+num);
    }

	exec('node '+path+'getKebiao.js '+num,function(err,stdout,stderr){
	 if(err) {
		 console.log('error:'+stderr);
	 }else{
		fs.writeFileSync(path+num+'/'+fname,stdout);
		fs.writeFileSync(path+num+'/'+"SUCCESS","1");
	 }
	});
	
	
}