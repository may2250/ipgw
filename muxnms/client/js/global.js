function gbl_restart() {
    if(globalObj.timerID != undefined){
        clearInterval(globalObj.timerID);
    }
	$('.main-content').empty();
	$('.main-content').append(
		'<div class="src_content">'
			+'<fieldset>'
				+'<legend>重启设备</legend>'
				
				+'<div class="src_btn">'
					+'<button class="btn_restart">重启设备</button>'
					+'<p class="gbltips"></p>'
				+'</div>'
			+'</fieldset>'
		+'</div>'
	);
	
	$( ".btn_restart" ).button({
      icons: {
        primary: "ui-icon-power"
      }
    }).click(function( event ) {
        event.preventDefault();
		$.ajax({
			 type: "GET",
			 async:false,
			 url: "http://"+localip+":4000/do/globalopt/reboot",
			 dataType: "json",
			 success: function(data){
                 if(data.sts == 1){
                     $('.gbltips').empty();
                     $('.gbltips').append('设备重启命令已下发，请30秒后尝试重新连接');
                 }else if(data.sts == 5){
                     alert("权限不足，请与管理员联系");
                 }
			 },    
			 error : function(err) {   
				alert("异常！====="+err);    
			 }   
		});
	});
}

function gbl_reset() {
    if(globalObj.timerID != undefined){
        clearInterval(globalObj.timerID);
    }
	$('.main-content').empty();
	$('.main-content').append(
		'<div class="src_content">'
			+'<fieldset>'
				+'<legend>恢复出厂设置</legend>'
				+'<div class="src_btn">'
					+'<button class="btn_reset">恢复出厂设置</button>'
					+'<p class="gbltips"></p>'
				+'</div>'
			+'</fieldset>'
		+'</div>'
	);
	
	$( ".btn_reset" ).button({
      icons: {
        primary: "ui-icon-refresh"
      }
    }).click(function( event ) {
        event.preventDefault();
		$.ajax({
			 type: "GET",
			 async:false,
			 url: "http://"+localip+":4000/do/globalopt/reset",
			 dataType: "json",
			 success: function(data){
                 if(data.sts == 1){
                     $('.gbltips').empty();
                     $('.gbltips').append('恢复出厂设置命令已下发，请30秒后尝试重新连接');
                 }else if(data.sts == 5){
                     alert("权限不足，请与管理员联系");
                 }
			 },    
			 error : function(err) {   
				alert("异常！====="+err);    
			 }   
		});
	});
}

function gbl_setIp() {
    if(globalObj.timerID != undefined){
        clearInterval(globalObj.timerID);
    }
	$('.main-content').empty();
	$('.main-content').append(
		'<div class="src_content">'
			+'<fieldset>'
				+'<legend>网络配置</legend>'
				+'<div class="network_set">'
					+'<table class="nettable">'
						+'<tr>'
							+'<td><label>新IP地址：</label></td>'
							+'<td><input type="text" value="" class="newip" /></td>'
							+'<td><label style="display:none;width:150px;color:red;margin-right:20px" class="ipvalidate">非法的IP地址!!</label></td>'
						+'</tr>'
						+'<tr>'
							+'<td><label>新网关地址：</label></td>'
							+'<td><input type="text" value="" class="newgateway" /></td>'
							+'<td><label style="display:none;width:150px;color:red;margin-right:20px" class="gatewayvalidate">非法的网关地址!!</label></td>'
						+'</tr>'
						+'<tr>'
							+'<td><label>新子网掩码：</label></td>'
							+'<td><input type="text" value="" class="newsubmask" /></td>'
							+'<td><label style="display:none;width:150px;color:red;margin-right:20px" class="submaskvalidate">非法的网关地址!!</label></td>'
						+'</tr>'
						+'<tr>'
							+'<td></td>'
							+'<td><button class="btn_set" style="float:right;margin:10px 30px">配置</button></td>'
							+'<td></td>'
						+'</tr>'
					+'</table>'
					+'<p class="settip"></p>'
				+'</div>'
			+'</fieldset>'
		+'</div>'
	);
	
	$( ".btn_set" ).button({
      icons: {
        primary: "ui-icon-gear"
      }
    }).click(function( event ) {
        event.preventDefault();
		var re=/^(\d+)\.(\d+)\.(\d+)\.(\d+)$/;//正则表达式     
	    if(re.test($(".newip").val()))     
	    {     
		   if( !(RegExp.$1<256 && RegExp.$2<256 && RegExp.$3<256 && RegExp.$4<256)) {
				$(".ipvalidate").css("display", "");
				return false; 
			}		       
	    }else{
			$(".ipvalidate").css("display", "");    
			return false; 
		}
		if(re.test($(".newgateway").val()))     
	    {     
		   if( !(RegExp.$1<256 && RegExp.$2<256 && RegExp.$3<256 && RegExp.$4<256)) {
				$(".gatewayvalidate").css("display", "");
				return false; 
			}		       
	    }else{
			$(".gatewayvalidate").css("display", "");    
			return false; 
		}
		if(re.test($(".newsubmask").val()))     
	    {     
		   if( !(RegExp.$1<256 && RegExp.$2<256 && RegExp.$3<256 && RegExp.$4<256)) {
				$(".submaskvalidate").css("display", "");
				return false; 
			}		       
	    }else{
			$(".submaskvalidate").css("display", "");    
			return false; 
		}
		$(".ipvalidate").css("display", "none");
		$(".gatewayvalidate").css("display", "none");
		$(".submaskvalidate").css("display", "none");
		$('.settip').empty();
		$('.settip').append('设置命令已下发，请尝试重新连接');
		$.ajax({
			 type: "GET",
			 async:false,
			 url: "http://"+localip+":4000/do/globalopt/setDevip?"+$(".newip").val()+"&"+$(".newgateway").val()+"&"+$(".newsubmask").val(),
			 dataType: "json",
			 success: function(data){
                 if(data.sts == 1){
                     $('.settip').empty();
                     $('.settip').append('设置命令已下发，请尝试重新连接');
                 }else if(data.sts == 5){
                     alert("权限不足，请与管理员联系");
                 }
			 },    
			 error : function(err) {
                 $('.settip').empty();
                 $('.settip').append('下发失败，未知错误!');
			 }   
		});
	});
}

function gbl_password() {
    if(globalObj.timerID != undefined){
        clearInterval(globalObj.timerID);
    }
    $('.main-content').empty();
    $('.main-content').append(
        '<div class="src_content">'
            +'<fieldset>'
                +'<legend>修改密码</legend>'
                +'<div class="register_form">'
                    +'<div class="register_formrow">'
                        +'<div class="register_item rlb"><label>原密码</label></div>'
                        +'<div class="register_item rip"><input type="password" class="oldpassword" placeholder="password" /> </div>'
                    +'</div>'
                    +'<div class="register_formrow">'
                        +'<div class="register_item rlb"><label>新密码</label></div>'
                        +'<div class="register_item rip"><input type="password" class="newpassword" placeholder="Password" /> </div>'
                    +'</div>'
                    +'<div class="register_formrow">'
                        +'<div class="register_item rlb"><label>密码确认</label></div>'
                        +'<div class="register_item rip"><input type="password" class="cpassword" placeholder="Password" /> </div>'
                    +'</div>'
                +'</div>'
                +'<div class="src_btn">'
                    +'<button class="btn_submit">修改</button>'
                    +'<p></p>'
                +'</div>'
            +'</fieldset>'
        +'</div>'
    );

    $( ".btn_submit" ).button({
        icons: {
            primary: "ui-icon-gear"
        }
    }).click(function( event ) {
        event.preventDefault();
        if($(".newpassword").val() != $(".cpassword").val()){
            alert("两次新密码输入不一致");
            return;
        }
        var strjson = '{oldpassword:'+$(".oldpassword").val() + ',newpassword:'+ $(".newpassword").val()
            +  '}';
        $.ajax({
            type: "GET",
            async:false,
            url: "http://"+localip+":4000/do/globalopt/setPassword",
            data: strjson,
            dataType: "json",
            success: function(data){
                if(data.sts == 1){
                    $(".oldpassword").val("");
                    $(".newpassword").val("");
                    $(".cpassword").val("");
                    alert("密码修改成功");
                }else if(data.sts == 5){
                    alert("权限不足，请与管理员联系");
                }
            },
            error : function(err) {
                alert("异常！====="+err);
            }
        });
    });
}

function gbl_monitor() {
    if(globalObj.timerID != undefined){
        clearInterval(globalObj.timerID);
    }
    $('.main-content').empty();
    $('.main-content').append(
        '<div class="src_content">'
            +'<fieldset>'
                +'<legend>输出通道[1] 比特率</legend>'
                +'<div id="canvasDiv">'
                +'</div>'
            +'</fieldset>'
            +'<div class="outsts">'
                +'<lable class="outch1">输出通道[CHN-1]溢出</lable>'
                +'<img class="outch1stsimg stsimg" />'
            +'</div>'
            +'<fieldset>'
                +'<legend>输出通道[2] 比特率</legend>'
                    +'<div id="canvasDiv2">'
                +'</div>'
            +'</fieldset>'
            +'<div class="outsts">'
                +'<lable class="outch2">输出通道[CHN-2]溢出</lable>'
                +'<img class="outch2stsimg stsimg" />'
            +'</div>'
            +'<table class="monitortable">'
                +'<tr>'
                    +'<td><label>有效输入数据丢失</label></td>'
                    +'<td><img class="inchsts1img stsimg" src="img/circle16_green.ico" /></td>'
                    +'<td><img class="inchsts2img stsimg" src="img/circle16_green.ico" /></td>'
                    +'<td><img class="inchsts3img stsimg" src="img/circle16_green.ico" /></td>'
                    +'<td><img class="inchsts4img stsimg" src="img/circle16_green.ico" /></td>'
                    +'<td><img class="inchsts5img stsimg" src="img/circle16_green.ico" /></td>'
                    +'<td><img class="inchsts6img stsimg" src="img/circle16_green.ico" /></td>'
                    +'<td><img class="inchsts7img stsimg" src="img/circle16_green.ico" /></td>'
                    +'<td><img class="inchsts8img stsimg" src="img/circle16_green.ico" /></td>'
                +'</tr>'
                +'<tr>'
                    +'<td class="tbl_right"><label>通道</label></td>'
                    +'<td class="tbl_center"><label>[1]</label></td>'
                    +'<td class="tbl_center"><label>[2]</label></td>'
                    +'<td class="tbl_center"><label>[3]</label></td>'
                    +'<td class="tbl_center"><label>[4]</label></td>'
                    +'<td class="tbl_center"><label>[5]</label></td>'
                    +'<td class="tbl_center"><label>[6]</label></td>'
                    +'<td class="tbl_center"><label>[7]</label></td>'
                    +'<td class="tbl_center"><label>[8]</label></td>'
                +'</tr>'
            +'</table>'
        +'</div>'
    );
     var flow = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];
    var flow2 = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];
    //创建随机数据源
    var create = function (){
        //获取最新输出比特率
        var data = [
            {
                name : '',
                value:flow,
                color:'#0d8ecf',
                line_width:2
            }
        ];
        return function(){
            return data;
        }
    }();

    var line = new iChart.LineBasic2D({
        render : 'canvasDiv',
        data: create(),
        align:'center',
        width : 800,
        height : 150,
        footnote : {
            text:'单位：Mb',
            color:'#black'
        },
        sub_option:{
            smooth : true,//平滑曲线
            point_size:10
        },
        tip:{
            enable:false,
            shadow:false
        },
        legend : {
            enable : false
        },
        crosshair:{
            enable:true,
            line_color:'#62bce9'
        },
        coordinate:{
            width:600,
            height:260,
            axis:{
                color:'#9f9f9f',
                width:[0,0,2,2]
            },
            grids:{
                vertical:{
                    way:'share_alike',
                    value:5
                }
            },
            scale:[{
                position:'left',
                start_scale:0,
                end_scale:50,
                scale_space:5,
                scale_size:2,
                scale_color:'#9f9f9f'
            }]
        }
    });
    //开始画图
    line.draw();

    var line2 = new iChart.LineBasic2D({
        render : 'canvasDiv2',
        data: create(),
        align:'center',
        width : 800,
        height : 150,
        footnote : {
            text:'单位：Mb',
            color:'#black'
        },
        sub_option:{
            smooth : true,//平滑曲线
            point_size:10
        },
        tip:{
            enable:false,
            shadow:false
        },
        legend : {
            enable : false
        },
        crosshair:{
            enable:true,
            line_color:'#62bce9'
        },
        coordinate:{
            width:600,
            height:260,
            axis:{
                color:'#9f9f9f',
                width:[0,0,2,2]
            },
            grids:{
                vertical:{
                    way:'share_alike',
                    value:5
                }
            },
            scale:[{
                position:'left',
                start_scale:0,
                end_scale:50,
                scale_space:5,
                scale_size:2,
                scale_color:'#9f9f9f'
            }]
        }
    });
    //开始画图
    line2.draw();

    var reloadchart = function (){
        //获取最新输出比特率
        $.ajax({
            type: "GET",
            async:false,
            url: "http://"+localip+":4000/do/globalopt/getmonitorinfo",
            dataType: "json",
            success: function(data){
                if((data.outValidBitrate != null) && (data.outValidBitrate != undefined)){
                    var nd = data.outValidBitrate/1000 + '.' + data.outValidBitrate%1000;
                    flow.shift();
                    flow.push(parseFloat(nd).toFixed(2));
                }
                switch(data.outstatus) {
                    case 0:
                        $('.outch1stsimg')[0].src = "img/circle16_green.ico";
                        break;
                    case 1:
                        $('.outch1stsimg')[0].src = "img/circle16_error.ico";
                        break;
                    case 2:
                        $('.outch1stsimg')[0].src = "img/circle16_error.ico";
                        break;
                }
                if((data.outValidBitrate2 != null) && (data.outValidBitrate2 != undefined)){
                    var nd = data.outValidBitrate2/1000 + '.' + data.outValidBitrate2%1000;
                    flow2.shift();
                    flow2.push(parseFloat(nd).toFixed(2));
                }
                switch(data.outstatus2) {
                    case 0:
                        $('.outch2stsimg')[0].src = "img/circle16_green.ico";
                        break;
                    case 1:
                        $('.outch2stsimg')[0].src = "img/circle16_error.ico";
                        break;
                    case 2:
                        $('.outch2stsimg')[0].src = "img/circle16_error.ico";
                        break;
                }
                $.each(data.children, function(index, item){
                    switch(item.ch){
                        case 1:
                            if(item.sts == 0){
                                $('.inchsts1img')[0].src = "img/circle16_green.ico";
                            }else{
                                $('.inchsts1img')[0].src = "img/circle16_error.ico";
                            }
                            break;
                        case 2:
                            if(item.sts == 0){
                                $('.inchsts2img')[0].src = "img/circle16_green.ico";
                            }else{
                                $('.inchsts2img')[0].src = "img/circle16_error.ico";
                            }
                            break;
                        case 3:
                            if(item.sts == 0){
                                $('.inchsts3img')[0].src = "img/circle16_green.ico";
                            }else{
                                $('.inchsts3img')[0].src = "img/circle16_error.ico";
                            }
                            break;
                        case 4:
                            if(item.sts == 0){
                                $('.inchsts4img')[0].src = "img/circle16_green.ico";
                            }else{
                                $('.inchsts4img')[0].src = "img/circle16_error.ico";
                            }
                            break;
                        case 5:
                            if(item.sts == 0){
                                $('.inchsts5img')[0].src = "img/circle16_green.ico";
                            }else{
                                $('.inchsts5img')[0].src = "img/circle16_error.ico";
                            }
                            break;
                        case 6:
                            if(item.sts == 0){
                                $('.inchsts6img')[0].src = "img/circle16_green.ico";
                            }else{
                                $('.inchsts6img')[0].src = "img/circle16_error.ico";
                            }
                            break;
                        case 7:
                            if(item.sts == 0){
                                $('.inchsts7img')[0].src = "img/circle16_green.ico";
                            }else{
                                $('.inchsts7img')[0].src = "img/circle16_error.ico";
                            }
                            break;
                        case 8:
                            if(item.sts == 0){
                                $('.inchsts8img')[0].src = "img/circle16_green.ico";
                            }else{
                                $('.inchsts8img')[0].src = "img/circle16_error.ico";
                            }
                            break;
                    }
                });
            },
            error : function(err) {
            }
        });
        var data = [
            {
                name : '',
                value:flow,
                color:'#0d8ecf',
                line_width:2
            }
        ];
        var data2 = [
            {
                name : '',
                value:flow2,
                color:'#0d8ecf',
                line_width:2
            }
        ];
        line.load(data);//载入新数据
        line2.load(data2);//载入新数据
    }

    //创建定时器定时获取输出比特率
    globalObj.timerID = setInterval(reloadchart,2000);

}

function gbl_import() {
    if(globalObj.timerID != undefined){
        clearInterval(globalObj.timerID);
    }
    $('.main-content').empty();
    $('.main-content').append(
        '<div class="src_content">'
        +'<fieldset>'
            +'<legend>配置导入</legend>'
            +'<form method="post" action="/upload/upload.esp" enctype="multipart/form-data">'
                +'<input type="hidden" name="MAX_FILE_SIZE" value="30000">'
                +'<table border="0">'
                +'<tr><td>Name</td><td><input type="text" name="Name"></td></tr>'
                +'<tr><td>Address</td><td><input type="text" name="Address"></td></tr>'
                +'<tr><td>Photo:</td><td><input type="file" name="photo"></td></tr>'
                +'</table>'
                +'<input type="submit" value="send">'
                +'<input type="reset" value="cancel">'
            +'</form>'
        +'</fieldset>'
        +'</div>'
    );
}