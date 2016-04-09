var http = require('http'),
    iconv = require('iconv-lite'),
    urlencode = require('urlencode'),
    hostname = 'http://jwzx.cqupt.edu.cn/';
    name = process.argv[2] || '';

var str = urlencode(name, 'gbk');
if (name === '') {
    console.log('please input: node index.js (teacher name)');
} else {
    http.get('http://jwzx.cqupt.edu.cn/pubTeaKebiao.php?searchKey=' + str, function (res) {
        var chunks = [], data, link;

        res.on('data', function (chunk) {
	
	//	console.log(chunk);
            chunks.push(chunk);
        });
        res.on('end', function () {
		
            data = iconv.decode(Buffer.concat(chunks), 'gb2312');
			var chunks = [], data, kebiao, classNum,
                    array = [],
                    Time = ['一二节', '三四节', '五六节', '七八节', '九十节', '十一十二节'],
                    Day = ['周一', '周二', '周三', '周四', '周五', '周六', '周日'];
            link = hostname + data.match(/<a.*<\/a>/)[0].match(/href=\'(.*)\'/)[1];
            http.get(link, function (res) {
			
                var chunks = [], data, kebiao, classNum,
                    array = [],
                    Time = ['一二节', '三四节', '五六节', '七八节', '九十节', '十一十二节'],
                    Day = ['周一', '周二', '周三', '周四', '周五', '周六', '周日'];
			
                res.on('data', function (chunk) {
                    chunks.push(chunk);
                });
				
                res.on('end', function () {
				
                    data = iconv.decode(Buffer.concat(chunks), 'gb2312');
                    kebiao = data.match(/<tr>[\s\S]*<\/tr>/gi)[0];//[\s\S]匹配非换行符之外的字符
                    array = kebiao.split('</tr><tr>');
					
                    array.forEach(function (ele, i) {
					
                        var tab = i;
                        tab === 0 ? '' : ele.split('</td><td').forEach(function (ele, j) {
                            if (ele === ' >&nbsp;' || ele === ' >&nbsp;</td>' || ele === ' >&nbsp;</td></tr>') {
                                return false;
                            } else if (ele.match(/title/g)) {
                                return false;
                            } else {
                                debugger;
                               // console.log(ele);
                                classNum = ele.match(/<BR>/g).length;
								var kebiaoPrefix='http://jwzx.cqupt.edu.cn/new/labkebiao/';
                                if (classNum === 1) {
                                    console.log('>>>' + Day[j - 1] + ',' + Time[tab - 1] + '<<<');
									var kburl=kebiaoPrefix+ele.match(/href=\'(.*)\'/)[1];
									 http.get(link, function (res) {
										res.on('data', function (chunk) {
											chunks.push(chunk);
										});
										res.on('end', function () {
											data = iconv.decode(Buffer.concat(chunks), 'gb2312');
											//todo
										});
									});
                                    console.log('课程:' + ele.match(/>&nbsp;(.*)<br>/)[1]);
                                    console.log('专业:' + ele.match(/<BR>(.*)<br>班级/)[1]);
                                    console.log('类型:' + ele.match(/color=#ff0000>(.*)<\/font>/)[1]);
                                    console.log('周数:' + ele.match(/<br>(.*)<br><font/)[1]);
                                    console.log('教室:' + ele.match(/<br>(.*)\b/)[1]);
                                    console.log('班级:' + ele.match(/<br>班级：(.*)<br><a/)[1]);
                                    console.log('');
                                } else {
									
                                    var tabs = ele.split('<br>');
									
                                    console.log('>>>' + Day[j - 1] + ',' + Time[tab - 1] + '<<<');
                                    for (var k = 0; k < classNum; k++) {
										var kburl=kebiaoPrefix+tabs[5+k*7].match(/href=\'(.*)\'/)[1];
										//todo
										//console.log(tabs);
                                        console.log('课程:' + tabs[0 + k * 7].replace(' >&nbsp;', ''));
                                        console.log('专业:' + tabs[3 + k * 7].match(/BR>(.*)/)[1]);
                                        console.log('类型:' + tabs[3 + k * 7].match(/0>(.*)<\/font>/)[1]);
                                        console.log('周数:' + tabs[2 + k * 7]);
                                        console.log('教室:' + tabs[1 + k * 7].match(/(.*)\r\n/)[1]);
                                        console.log('班级:' + tabs[4 + k * 7].replace('班级：', ''));
                                        if (k !== (classNum - 1)) {
                                            console.log('---');
                                        }
                                    }
                                    console.log('');
                                }
                            }
                        });;
                    });
                });
            });
        });
    });    
}

