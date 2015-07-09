function gbl_restart() {
    if(globalObj.timerID != undefined){
        clearInterval(globalObj.timerID);
    }
	$('.main-content').empty();
	$('.main-content').append(
		'<div class="src_content">'
			+'<fieldset>'
				+'<legend class="i18n_RESTART">重启设备</legend>'
				
				+'<div class="src_btn">'
					+'<button class="btn_restart i18n_RESTART">重启设备</button>'
					+'<p class="gbltips"></p>'
				+'</div>'
			+'</fieldset>'
		+'</div>'
	);
	$.i18n.properties({
        name : globalObj._nv, //资源文件名称
        path : '/i18n/', //资源文件路径
        mode : 'map', //用Map的方式使用资源文件中的值
        language : globalObj._nv,
        callback : function() {//加载成功后设置显示内容
            $('.i18n_RESTART').html($.i18n.prop('RESTART'));           
            $('.i18n_RESTART')[1].textContent = $.i18n.prop('RESTART');
            
        }
    });
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
                     $('.gbltips').append(globalObj._nv == "zh-CN"?"设备重启命令已下发，请30秒后尝试重新连接":"Device is Rebooting, pls waitting 30sec to reload....");
                 }else if(data.sts == 5){
                     alert(globalObj._nv == "zh-CN"?"该用户权限不足.":"Permission Denied!");
                 }
			 },    
			 error : function(err) {   
				//alert("异常！====="+err);
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
				+'<legend class="i18n_RESTOREDEFAULT">恢复出厂设置</legend>'
				+'<div class="src_btn">'
					+'<button class="btn_reset i18n_RESTOREDEFAULT">恢复出厂设置</button>'
					+'<p class="gbltips"></p>'
				+'</div>'
			+'</fieldset>'
		+'</div>'
	);
	$.i18n.properties({
        name : globalObj._nv, //资源文件名称
        path : '/i18n/', //资源文件路径
        mode : 'map', //用Map的方式使用资源文件中的值
        language : globalObj._nv,
        callback : function() {//加载成功后设置显示内容
            $('.i18n_RESTOREDEFAULT').html($.i18n.prop('RESTOREDEFAULT'));           
            $('.i18n_RESTOREDEFAULT')[1].textContent = $.i18n.prop('RESTOREDEFAULT');            
        }
    });
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
                     $('.gbltips').append(globalObj._nv == "zh-CN"?"恢复出厂设置命令已下发，请30秒后尝试重新连接":"Device restored, pls waitting 30secs to reload...");
                 }else if(data.sts == 5){
                     alert(globalObj._nv == "zh-CN"?"该用户权限不足.":"Permission Denied!");
                 }else{
                     alert(globalObj._nv == "zh-CN"?"恢复出厂设置命令已下发异常，请30秒后尝试重新连接":"Device restored error, pls waitting 30secs to reload...");
                 }
			 },    
			 error : function(err) {   
				//alert("异常！====="+err);
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
				+'<legend class="i18n_NETSETTING">网络配置</legend>'
				+'<div class="network_set">'
					+'<table class="nettable">'
						+'<tr>'
							+'<td><label class="i18n_NEWIP">新IP地址：</label></td>'
							+'<td><input type="text" value="" class="newip" /></td>'
							+'<td><label style="display:none;width:150px;color:red;margin-right:20px" class="ipvalidate i18n_ILLEGALIP">非法的IP地址!!</label></td>'
						+'</tr>'
						+'<tr>'
							+'<td><label class="i18n_NEWGATEWAY">新网关地址：</label></td>'
							+'<td><input type="text" value="" class="newgateway" /></td>'
							+'<td><label style="display:none;width:150px;color:red;margin-right:20px" class="gatewayvalidate i18n_ILLEGALGATEWAY">非法的网关地址!!</label></td>'
						+'</tr>'
						+'<tr>'
							+'<td><label class="i18n_NEWSUBMASK">新子网掩码：</label></td>'
							+'<td><input type="text" value="" class="newsubmask" /></td>'
							+'<td><label style="display:none;width:150px;color:red;margin-right:20px" class="submaskvalidate i18n_ILLEGALSUBMASK">非法的网关地址!!</label></td>'
						+'</tr>'
						+'<tr>'
							+'<td></td>'
							+'<td><button class="btn_set i18n_BTNCONFIG" style="float:right;margin:10px 30px">配置</button></td>'
							+'<td></td>'
						+'</tr>'
					+'</table>'
					+'<p class="settip"></p>'
				+'</div>'
			+'</fieldset>'
		+'</div>'
	);
	$.i18n.properties({
        name : globalObj._nv, //资源文件名称
        path : '/i18n/', //资源文件路径
        mode : 'map', //用Map的方式使用资源文件中的值
        language : globalObj._nv,
        callback : function() {//加载成功后设置显示内容
            $('.i18n_NETSETTING').html($.i18n.prop('NETSETTING'));
            $('.i18n_NEWIP').html($.i18n.prop('NEWIP'));
            $('.i18n_ILLEGALIP').html($.i18n.prop('ILLEGALIP'));
            $('.i18n_NEWGATEWAY').html($.i18n.prop('NEWGATEWAY'));
            $('.i18n_ILLEGALGATEWAY').html($.i18n.prop('ILLEGALGATEWAY'));
            $('.i18n_NEWSUBMASK').html($.i18n.prop('NEWSUBMASK'));            
            $('.i18n_ILLEGALSUBMASK').html($.i18n.prop('ILLEGALSUBMASK'));            
            $('.i18n_BTNCONFIG')[0].textContent = $.i18n.prop('BTNCONFIG');            
        }
    });
	$( ".btn_set" ).button({
      icons: {
        primary: "ui-icon-gear"
      }
    }).click(function( event ) {
        event.preventDefault();
		var re=/^(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$/;//正则表达式
	    if(!re.test($(".newip").val()))
	    {
            $(".ipvalidate").css("display", "");
            return false;
	    }else{
            $(".ipvalidate").css("display", "none");
        }
		if(!re.test($(".newgateway").val()))
	    {
            $(".gatewayvalidate").css("display", "");
            return false;
        }else{
            $(".gatewayvalidate").css("display", "none");
        }
		if(!re.test($(".newsubmask").val()))
	    {
            $(".submaskvalidate").css("display", "");
            return false;
        }else{
            $(".submaskvalidate").css("display", "none");
        }

		$('.settip').empty();
		$('.settip').append(globalObj._nv == "zh-CN"?"设置命令已下发，请尝试重新连接":"Sending config, pls try to reload...");
		$.ajax({
			 type: "GET",
			 async:false,
			 url: "http://"+localip+":4000/do/globalopt/setDevip?"+$(".newip").val()+"&"+$(".newgateway").val()+"&"+$(".newsubmask").val(),
			 dataType: "json",
			 success: function(data){
                 if(data.sts == 1){
                     $('.settip').empty();
                     $('.settip').append(globalObj._nv == "zh-CN"?"设置命令已下发，请尝试重新连接":"Sending config, pls try to reload...");
                 }else if(data.sts == 5){
                     alert(globalObj._nv == "zh-CN"?"该用户权限不足.":"Permission Denied!");
                 }
			 },
			 error : function(err) {
                 $('.settip').empty();
                 $('.settip').append(globalObj._nv == "zh-CN"?"下发失败，未知错误!":"Sending failed, unknown error!");
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
                +'<legend class="i18n_CHANGEPASSWORD">修改密码</legend>'
                +'<div class="register_form">'
                    +'<div class="register_formrow">'
                        +'<div class="register_item rlb"><label class="i18n_OLDPASSWORD">原密码</label></div>'
                        +'<div class="register_item rip"><input type="password" class="oldpassword" placeholder="password" /> </div>'
                    +'</div>'
                    +'<div class="register_formrow">'
                        +'<div class="register_item rlb"><label class="i18n_NEWPASSWORD">新密码</label></div>'
                        +'<div class="register_item rip"><input type="password" class="newpassword" placeholder="Password" /> </div>'
                    +'</div>'
                    +'<div class="register_formrow">'
                        +'<div class="register_item rlb"><label class="i18n_CONFIRMPASSWORD">密码确认</label></div>'
                        +'<div class="register_item rip"><input type="password" class="cpassword" placeholder="Password" /> </div>'
                    +'</div>'
                +'</div>'
                +'<div class="src_btn">'
                    +'<button class="btn_submit i18n_MODIFY">修改</button>'
                    +'<p></p>'
                +'</div>'
            +'</fieldset>'
        +'</div>'
    );
    $.i18n.properties({
        name : globalObj._nv, //资源文件名称
        path : '/i18n/', //资源文件路径
        mode : 'map', //用Map的方式使用资源文件中的值
        language : globalObj._nv,
        callback : function() {//加载成功后设置显示内容
            $('.i18n_CHANGEPASSWORD').html($.i18n.prop('CHANGEPASSWORD'));
            $('.i18n_OLDPASSWORD').html($.i18n.prop('OLDPASSWORD'));
            $('.i18n_NEWPASSWORD').html($.i18n.prop('NEWPASSWORD'));
            $('.i18n_CONFIRMPASSWORD').html($.i18n.prop('CONFIRMPASSWORD'));           
            $('.i18n_MODIFY')[0].textContent = $.i18n.prop('MODIFY');            
        }
    });
    $( ".btn_submit" ).button({
        icons: {
            primary: "ui-icon-gear"
        }
    }).click(function( event ) {
        event.preventDefault();
        if($(".newpassword").val() != $(".cpassword").val()){
            alert(globalObj._nv == "zh-CN"?"两次新密码输入不一致":"Two new password input is not consistent.");
            return;
        }
        if($(".oldpassword").val() == "" || $(".newpassword").val() == ""){
            alert(globalObj._nv == "zh-CN"?"密码不能为空.":"Password can not be null.");
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
                    alert(globalObj._nv == "zh-CN"?"密码修改成功":"Password changed successful.");
                }else if(data.sts == 5){
                    alert(globalObj._nv == "zh-CN"?"该用户权限不足.":"Permission Denied!");
                }else if(data.sts == 0){
                    alert(globalObj._nv == "zh-CN"?"原密码输入不正确.":"Old password error.");
                }
            },
            error : function(err) {
                //alert("异常！====="+err);
            }
        });
    });
}
