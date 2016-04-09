var fs= require('fs') ;
 var request = require('request'),
    iconv = require('iconv-lite'),
    urlencode = require('urlencode');
var	kburl = process.argv[2] || '';
var	teanum = process.argv[3] || '';
var number= process.argv[4] || '';
var path='E:/QTWorkspace/tmpjs/'+teanum+'/';

if (kburl == ''||number=='') {
    console.log('please input: node getMingdan.js kburl');
} else {
	var tmpf=number+'.tmp.txt';
	request({
		encoding: null,
		url: kburl
	}, function(error, response, body) {
    if (!error && response.statusCode == 200) {
        data=iconv.decode(body, 'gb2312').toString();
		data=data.replace(/<style[\s\S]*<\/style>/," ").replace(/<[^>]*>/g," ")
				.replace(/[\s]+/g,"\n");
				//.replace(//g," ");
		fs.writeFileSync(path+tmpf, data);
    }
	});
}
