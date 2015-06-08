var globalObj = {
    _outtable: null,
    timerID: undefined
};

var channel_root = [
    {"title": "输入通道", folder: true, key: "id1.0", expanded: true, "expanded": true, "icon": "img/book.ico"}
];

var StreamData = [];

createHomeUI();

function getprgs(){
    $.ajax({
        type: "GET",
        async:true,
        url: "http://"+localip+":4000/do/programs/getPrgs",
        dataType: "json",
        success: function(res){
            if(res.sts == 6){
                alert("通讯错误");
            }else if(res.sts == 8){
                window.location = "/login.esp";
            }else{
                var devlisttree = $("#devlist").fancytree("getTree");
                devlisttree.reload();
                var node = devlisttree.getNodeByKey("id1.0");
                res = JSON.stringify(res).replace('\\','');
                var treeData = JSON.parse(res);
                node.addChildren(treeData);
            }
        },
        error : function(err) {
            alert("AJAX ERROR---getPrgs!!");
        }
    });
}

function ipread(flag){
    $.ajax({
        type: "GET",
        async:true,
        url: "http://"+localip+":4000/do/programs/ipRead",
        dataType: "json",
        success: function(res){
            if(res.sts == 6){
                alert("通讯错误");
            }else if(res.sts == 8){
                window.location = "/login.esp";
            }else{
                if(flag == 1){
                    $('.output_ttl').val(res.ttl);
                    $('.output_mode')[0].options[Number(res.dvbIptvMode)].selected = true;
                }else if(flag == 2){
                    //发送源
                    $('.s_netInterfaceMode')[0].options[Number(res.netInterfaceMode)].selected = true;
                    $('.s_ip').val(res.srcip);
                    $('.s_port').val(Number(res.port));
                    $('.s_mac').val(res.mac);
                }
            }
        },
        error : function(err) {
            alert("AJAX ERROR---ipRead!!");
        }
    });
}

function createHomeUI(){
    if(globalObj.timerID != undefined){
        clearInterval(globalObj.timerID);
    }
    $('.main-content').empty();
    $('.main-content').append(
        '<div class="src_content">'
            +'<div class="field_head">'
                +'<fieldset>'
                    +'<legend>发送设置</legend>'
                    +'<table class="fieldset_tbl">'
                        +'<tr>'
                            +'<td>'
                                +'<label class="lb_mr">输出模式</label>'
                                +'<select class="output_mode lb_mr">'
                                    +'<option value="0">MPTS</option>'
                                    +'<option value="1">SPTS</option>'
                                +'</select>'
                            +'</td>'
                            +'<td>'
                                +'<label class="lb_mr">TTL</label>'
                                +'<input class="output_ttl" type="text" />'
                                +'<label class="lb_mr">[0:255]</label>'
                            +'</td>'
                            +'<td>'
                                +'<label class="lb_mr">输出节目总数</label>'
                                +'<input class="output_cnt" type="text" />'
                            +'</td>'
                        +'</tr>'
                    +'</table>'
                +'</fieldset>'
            +'</div>'
            +'<div class="clearfix prg_content">'
                +'<div class="input_tree">'
                    +'<div class="input_spts">'
                        +'<lable class="lb_mr lb_ml">SPTS通道</lable>'
                        +'<select class="spts_ch lb_mr"></select>'
                        +'<a href="javascript:void()" class="btn_css btn_spts">确定</a>'
                    +'</div>'
                    +'<div class="tree_content">'
                        +'<div id="devlist" class="channel_input"></div>'
                    +'</div>'
                +'</div>'
                +'<div class="prg_detail">'
                    +'<table class="fieldset_tbl">'
                        +'<tr>'
                            +'<td><label class="lb_mr">通道</label></td>'
                            +'<td><input class="prg_ch lb_mr"></td>'
                            +'<td><a href="javascript:void()" class="btn_css btn_prg">确定</a></td>'
                        +'</tr>'
                        +'<tr>'
                            +'<td><label class="lb_mr">输出方式</label></td>'
                            +'<td><select class="prg_outmode">'
                                +'<option value="0">单播-UDP</option><option value="1">组播-UDP</option>'
                            +'</select></td>'
                            +'<td</td>'
                        +'</tr>'
                        +'<tr>'
                            +'<td><label class="lb_mr">目的IP地址</label></td>'
                            +'<td><input class="prg_destip" type="text" /></td>'
                            +'<td><label>(eg:192.168.1.103)</label></td>'
                        +'</tr>'
                        +'<tr>'
                            +'<td><label class="lb_mr">目的端口号</label></td>'
                            +'<td><input class="prg_destport" type="text" /></td>'
                            +'<td><label>(1~65535)</label></td>'
                        +'</tr>'
                        +'<tr>'
                            +'<td><label class="lb_mr">目的MAC</label></td>'
                            +'<td><input class="prg_destmac" type="text" /></td>'
                            +'<td><label>(eg:00:11:22:33:44:55)</label></td>'
                        +'</tr>'
                    +'</table>'
                    +'<div id="out_table">'
                        +'<table cellpadding="0" cellspacing="0" border="0" class="cell-border compact hover" id="tbl_outtable"></table>'
                    +'</div>'
                +'</div>'
            +'</div>'
            +'<div class="tbn_div">'
                +'<button id="output-search">搜索</button>'
                +'<button id="output-read">读取</button>'
                +'<button id="output-auto">自动映射</button>'
                +'<button id="output-clear">清空</button>'
                +'<button id="output-write">应用</button>'
            +'</div>'
        +'</div>'
    );

    $('.output_cnt').attr("disabled", true);
    $('.prg_ch').attr("disabled", true);
    $('.spts_ch').attr("disabled", true);
    $('.btn_spts').attr("disabled", true);
    //$('.input_spts').css("display", "none");
    $('.btn_spts').on("click", function(){
        alert("btn_spts click!");
    });

    $('.btn_prg').on("click", function(){
        alert("btn_prg click!");
    });

    $( "#output-search" ).button({
        icons: {
            primary: "ui-icon-search"
        }
    }).click(function( event ) {
        event.preventDefault();
        $.ajax({
            type: "GET",
            async: false,
            url: "http://"+localip+":4000/do/programs/search",
            dataType: "json",
            success: function(data){
                if(data.sts == 6){
                    alert("通讯错误");
                    return false;
                }
                getprgs();
                ipread(1);
            },
            error : function(err) {
                alert("AJAX ERROR---search!!");
            }
        });
    });

    $( "#output-read" ).button({
        icons: {
            primary: "ui-icon-comment"
        }
    }).click(function( event ) {
        event.preventDefault();
        getprgs();
        ipread(1);
    });

    $( "#output-auto" ).button({
        icons: {
            primary: "ui-icon-shuffle"
        }
    }).click(function( event ) {
        event.preventDefault();

    });

    $( "#output-clear" ).button({
        icons: {
            primary: "ui-icon-trash"
        }
    }).click(function( event ) {
        event.preventDefault();

    });

    $( "#output-write" ).button({
        icons: {
            primary: "ui-icon-pencil"
        }
    }).click(function( event ) {
        event.preventDefault();

    });

    //输入通道树
    $("#devlist").fancytree({
        checkbox: false,
        selectMode: 1,
        minExpandLevel:2,
        source: channel_root,
        select: function(event, data) {

        },
        click: function(event, data) {
            if( $.ui.fancytree.getEventTargetType(event) === "title" ){
                data.node.toggleSelected();
            }
        }
    });

    //右侧table
    var tout = $('#tbl_outtable').dataTable( {
        "data": StreamData,
        "order": [[ 0, "asc" ]],
        "paging":   false,
        "info":     false,
        "searching":   false,
        "width": 270,
        "scrollY": 265,
        "bAutoWidth": false,
        "columns": [
            { "title": "通道"},
            { "title": "输出方式"},
            { "title": "IP"},
            { "title": "端口号"},
            { "title": "MAC" },
            { "title": "节目名称" }
        ]
    });

}

function readinputsts(){
    $.ajax({
        type: "GET",
        async: true,
        url: "http://"+localip+":4000/do/programs/readinputsts",
        dataType: "json",
        success: function(res){
            if(res.sts == 6){
                alert("通讯错误");
            }else if(res.sts == 8){
                window.location = "/login.esp";
            }else{
                $('.s_inrate').val(res.bitrate/1000000);
                if(res.lockStatus){
                    $('.s_inlock')[0].src = "../img/circle16_green.ico";
                }else{
                    $('.s_inlock')[0].src = "../img/circle16_error.ico";
                }
            }
        },
        error : function(err) {
            alert("AJAX ERROR---readinputsts!!");
        }
    });
}

function createSendSrcUI(){
    if(globalObj.timerID != undefined){
        clearInterval(globalObj.timerID);
    }
    $('.main-content').empty();
    $('.main-content').append(
        '<div class="src_content">'
            +'<fieldset>'
                +'<legend>发送源</legend>'
                +'<div class="sendsrcdiv">'
                    +'<label class="lb_mr">网络接口模式</label>'
                    +'<select class="s_netInterfaceMode lb_mr"><option value="0">10M</option>'
                        +'<option value="1">100M</option><option value="2">1000M</option>'
                        +'<option value="3">------</option>'
                    +'</select>'
                    +'<label class="lb_mr">输入码率</label>'
                    +'<input class="s_inrate lb_mr" type="text" />Mbps'
                +'</div>'
                +'<div class="sendsrcdiv">'
                    +'<label class="lb_mr">源IP地址</label>'
                    +'<input class="s_ip lb_mr" pattern="^(25[0-5]|2[0-4]\\d|[0-1]?\\d?\\d)(\\.(25[0-5]|2[0-4]\\d|[0-1]?\\d?\\d)){3}$" type="text" />'
                    +'<label class="lb_mr">eg(192.168.1.103)</label>'
                +'</div>'
                +'<div class="sendsrcdiv">'
                    +'<label class="lb_mr">源端口号</label>'
                    +'<input class="s_port lb_mr" type="text" />'
                    +'<label class="lb_mr">[0~65535]</label>'
                    +'<label class="lb_mr">输入锁定</label>'
                    +'<img src="" class="s_inlock lb_mr" />'
                +'</div>'
                +'<div class="sendsrcdiv">'
                    +'<label class="lb_mr">源MAC</label>'
                    +'<input class="s_mac lb_mr" pattern="([0-9A-Fa-f]{2}-){5}[0-9A-Fa-f]{2})" type="text" />'
                    +'<label class="lb_mr">值为16进制</label>'
                    +'<label class="lb_mr">eg(00:11:22:33:44:55)</label>'
                +'</div>'
            +'</fieldset>'
        +'</div>'

        +'<div class="tbn_div">'
            +'<button id="src-read">读取</button>'
            +'<button id="src-write">应用</button>'
        +'</div>'
    );

    $('.s_inrate').attr("disabled", true);
    $('.s_netInterfaceMode').attr("disabled", true);

    ipread(2);
    //创建定时器定时获取输出比特率
    globalObj.timerID = setInterval(readinputsts,2000);

    $( "#src-read" ).button({
        icons: {
            primary: "ui-icon-comment"
        }
    }).click(function( event ) {
        event.preventDefault();
        ipread(2);
    });

    $( "#src-write" ).button({
        icons: {
            primary: "ui-icon-pencil"
        }
    }).click(function( event ) {
        event.preventDefault();
        if($('.s_port').val()>65535 || $('.s_port').val()<0){
            alert("端口号溢出.");
            return false;
        }
        var regexp = /^(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$/;
        var valid = regexp.test($('.s_ip').val());
        if(!valid){
            alert("无效的IP地址.");
            return false;
        }

        regexp = /[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}/;
        var valid = regexp.test($('.s_mac').val());
        if(!valid){
            alert("无效的MAC地址.");
            return false;
        }

        var jsonstr = '{"ip":"' + $('.s_ip').val() + '","port":' + $('.s_port').val() + ',"mac":"' + $('.s_mac').val() + '"}';
        $.ajax({
            type: "GET",
            async: false,
            url: "http://"+localip+":4000/do/programs/ParamsWriteAll",
            data: JSON.parse(jsonstr),
            dataType: "json",
            success: function(res){
                if(res.sts == 6){
                    alert("通讯错误");
                }else if(res.sts == 8){
                    window.location = "/login.esp";
                }else if(res.sts == 5){
                    alert("该用户权限不足.");
                }else{
                    alert("下发成功.");
                }
            },
            error : function(err) {
                alert("AJAX ERROR---ParamsWriteAll!!");
            }
        });
    });
}



