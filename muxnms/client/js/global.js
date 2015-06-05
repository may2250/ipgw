function gbl_restart() {
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
