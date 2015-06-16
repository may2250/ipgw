var globalObj = {
    _outtable: null,
    _devtree: null,
    timerID: undefined
};

var channel_root = [
    {"title": "输入通道", folder: true, key: "id1.0", expanded: true, "expanded": true, "icon": "img/book.ico"}
];

var StreamData = [];

createHomeUI();

var dig_notification = $( "#progress-notification" ).dialog({
    autoOpen: false,
    modal: true,
    width: 300
});

function getprgs(){
    $('.notification-tips')[0].textContent = "正在获取节目..."
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
        async: false,
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
                    $('.spts_ch').attr("disabled", true);
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

function iptvread(){
    $('.notification-tips')[0].textContent = "正在获取IPTV信息..."
    $.ajax({
        type: "GET",
        async: false,
        url: "http://"+localip+":4000/do/programs/iptvRead",
        dataType: "json",
        success: function(res){
            if(res.sts == 6){
                alert("通讯错误");
            }else if(res.sts == 8){
                window.location = "/login.esp";
            }else{

            }
        },
        error : function(err) {
            alert("AJAX ERROR---ipRead!!");
        }
    });
}

function outprgList(){
    $('.notification-tips')[0].textContent = "正在获取输出列表..."
    $.ajax({
        type: "GET",
        async: false,
        url: "http://"+localip+":4000/do/programs/outprgList",
        dataType: "json",
        success: function(data){
            if(data.sts == 6){
                alert("通讯错误");
            }else if(data.sts == 8){
                window.location = "/login.esp";
            }else{
                StreamData.length = 0;
                $('.output_cnt').val(data.prgcnt);
                $.each(data.children, function(key, itemv) {
                    var item = [itemv.index,itemv.modeStr, itemv.ipStr,itemv.port,itemv.macStr, itemv.nameStr];
                    StreamData[StreamData.length] = item;
                });
                //编辑节目对话框表
                if ( $.fn.dataTable.isDataTable( '#tbl_outtable' ) ) {
                    $('#tbl_outtable').dataTable().fnClearTable();
                    $('#tbl_outtable').dataTable().fnAddData(StreamData);
                }else{

                }
                var srow;
                $.each(data.children, function(key, itemv) {
                    if(itemv.Isoutprg){
                        srow = globalObj._outtable[0].rows[itemv.index];
                        $(srow).addClass('outprg');
                    }
                });

            }
        },
        error : function(err) {
            alert("AJAX ERROR---ipRead!!");
        }
    });
}

function setIpTvmode(mod){
    $.ajax({
        type: "GET",
        async: false,
        url: "http://"+localip+":4000/do/programs/setIpTvmode?mode="+mod,
        dataType: "json",
        success: function(data){
            if(data.sts == 6){
                alert("通讯错误");
            }else if(data.sts == 8){
                window.location = "/login.esp";
            }else{

            }
        },
        error : function(err) {
            alert("AJAX ERROR---setIpTvmode!!");
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
                        +'<select class="spts_ch"></select>'
                        +'<a href="javascript:void(0)" class="btn_css btn_spts">确定</a>'
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
                            +'<td><a href="javascript:void(0)" class="btn_css btn_prg">确定</a></td>'
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

    $('.btn_spts').on("click", function(){
        var selectednode = $("#devlist").fancytree("getTree").getActiveNode();
        if(selectednode != null && selectednode.data.prgnum != undefined){
            var prgId = selectednode.data.prgnum;
            var outChnId = isNaN($(".spts_ch").val())?0:$(".spts_ch").val();
            var jsonstr = '{"inCh":1,"prgId":' + prgId + ',"outChnId":' + outChnId + '}';
            $.ajax({
                type: "GET",
                async: false,
                url: "http://"+localip+":4000/do/programs/outchnprg_output",
                data: JSON.parse(jsonstr),
                dataType: "json",
                success: function(data){
                    if(data.sts == 6){
                        alert("通讯错误");
                        return false;
                    }
                    outprgList();
                },
                error : function(err) {
                    alert("AJAX ERROR---outchnprg_output!!");
                }
            });
        }
    });

    $('.btn_prg').on("click", function(){
        var outchn = $('.prg_ch').val();
        var outMode = $('.prg_outmode').get(0).selectedIndex;
        var ipstr = $('.prg_destip').val();
        var port = $('.prg_destport').val();
        var macstr = $('.prg_destmac').val();

        if(isNaN(port)){
            alert("非法的端口号.");
        }else{
            if(parseInt(port)<1 || parseInt(port)>65535){
                alert("非法的端口号.");
            }
        }
        var regexp = /^(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$/;
        var valid = regexp.test(ipstr);
        if(!valid){
            alert("无效的IP地址.");
            return false;
        }
        if(macstr != "Auto"){
            regexp = /[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}/;
            valid = regexp.test(macstr);
            if(!valid){
                alert("无效的MAC地址.");
                return false;
            }
        }
        var jsonstr = '{"outchn":"' + outchn + '","outMode":' + outMode + ',"macstr":"' + macstr + '","ipstr":"'
            + ipstr + '","port":' + port + '}';
        $.ajax({
            type: "GET",
            async: false,
            url: "http://"+localip+":4000/do/programs/outChnConfig",
            data: JSON.parse(jsonstr),
            dataType: "json",
            success: function(data){
                if(data.sts == 8){
                    window.location = "/login.esp";
                }else if(data.sts == 5){
                    alert("该用户权限不足.");
                    return false;
                }
                if(data.outMode < 3){
                    $('.prg_outmode')[0].selectedIndex = 0;
                }else if(data.outMode == 3){
                    $('.prg_outmode')[0].selectedIndex = 1;
                }
                //$('.prg_ch').val(index + 1);
                $('.prg_destip').val(data.ipStr);
                $('.prg_destport').val(data.port);
                $('.prg_destmac').val(data.macStr);
            },
            error : function(err) {
                alert("AJAX ERROR---outChnConfig!!");
            }
        });

    });

    $( "#output-search" ).button({
        icons: {
            primary: "ui-icon-search"
        }
    }).click(function( event ) {
        event.preventDefault();
        dig_notification.dialog( "open" );
        getprgs();
        ipread(1);
        iptvread();
        outprgList();
        dig_notification.dialog( "close" );
    });

    $( "#output-read" ).button({
        icons: {
            primary: "ui-icon-comment"
        }
    }).click(function( event ) {
        event.preventDefault();
        dig_notification.dialog( "open" );
        getprgs();
        ipread(1);
        iptvread();
        outprgList();
        dig_notification.dialog( "close" );

    });

    $( "#output-auto" ).button({
        icons: {
            primary: "ui-icon-shuffle"
        }
    }).click(function( event ) {
        event.preventDefault();
        $("#devlist").fancytree("getTree").getRootNode().setActive();
        $.ajax({
            type: "GET",
            async: false,
            url: "http://"+localip+":4000/do/programs/prgMuxSptsMap",
            dataType: "json",
            success: function(data){
                if(data.sts == 8){
                    window.location = "/login.esp";
                }else if(data.sts == 5){
                    alert("该用户权限不足.");
                    return false;
                }else if(data.sts == 1){
                    outprgList();
                }
            },
            error : function(err) {
                alert("AJAX ERROR---prgMuxSptsMap!!");
            }
        });
    });

    $( "#output-clear" ).button({
        icons: {
            primary: "ui-icon-trash"
        }
    }).click(function( event ) {
        event.preventDefault();
        $("#devlist").fancytree("getTree").getRootNode().setActive();
        $.ajax({
            type: "GET",
            async: false,
            url: "http://"+localip+":4000/do/programs/clearprgMux",
            dataType: "json",
            success: function(data){
                if(data.sts == 8){
                    window.location = "/login.esp";
                }else if(data.sts == 5){
                    alert("该用户权限不足.");
                    return false;
                }else if(data.sts == 1){
                    outprgList();
                }
            },
            error : function(err) {
                alert("AJAX ERROR---clearprgMux!!");
            }
        });
    });

    $( "#output-write" ).button({
        icons: {
            primary: "ui-icon-pencil"
        }
    }).click(function( event ) {
        event.preventDefault();
        $('.notification-tips')[0].textContent = "正在下发配置..."
        dig_notification.dialog( "open" );
        var ttl = $('.output_ttl').val();
        $.ajax({
            type: "GET",
            async: false,
            url: "http://"+localip+":4000/do/programs/muxprgwrite?ttl="+ttl,
            dataType: "json",
            success: function(data){
                dig_notification.dialog( "close" );
                if(data.sts == 8){
                    window.location = "/login.esp";
                }else if(data.sts == 5){
                    alert("该用户权限不足.");
                    return false;
                }else if(data.sts == 1){
                    //outprgList();
                }else if(data.sts == 2){
                    alert("检测到错误的IP输出通道设置！");
                }

            },
            error : function(err) {
                alert("AJAX ERROR---muxprgwrite!!");
            }
        });

    });

    //输入通道树
    globalObj._devtree = $("#devlist").fancytree({
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
            var snode = data.node;
            var arr = snode.key.match(/\./g);
            if(arr.length == 2){
                var prgnum = snode.data.prgnum;
                $.ajax({
                    type: "GET",
                    async: false,
                    url: "http://"+localip+":4000/do/programs/tree_selctdprg?prgnum="+prgnum,
                    dataType: "json",
                    success: function(data){
                        if(data.sts == 8){
                            window.location = "/login.esp";
                        }
                        $('.spts_ch').attr("disabled", false);
                        $(".spts_ch").empty();
                        $.each(data.children, function(index, item){
                            var option = $("<option>").val(item.tag).text(item.tag);
                            $(".spts_ch").append(option);
                        });
                        $('.spts_ch')[0].selectedIndex = data.tag;
                        var srow = globalObj._outtable[0].rows[$('.spts_ch').val()];
                        $('#tbl_outtable').DataTable().$('tr.selected').removeClass('selected');
                        $(srow).addClass('selected');
                        //$(srow).addClass('outprg');
                        if(srow != undefined){
                            var index = $(srow)[0].cells[0].textContent-1;
                            $.ajax({
                                type: "GET",
                                async: false,
                                url: "http://"+localip+":4000/do/programs/tbl_selctdprg?index="+index,
                                dataType: "json",
                                success: function(data){
                                    if(data.outMode < 3){
                                        $('.prg_outmode')[0].selectedIndex = 0;
                                    }else if(data.outMode == 3){
                                        $('.prg_outmode')[0].selectedIndex = 1;
                                    }
                                    $('.prg_ch').val(index + 1);
                                    $('.prg_destip').val(data.ipStr);
                                    $('.prg_destport').val(data.port);
                                    $('.prg_destmac').val(data.macStr);

                                },
                                error : function(err) {
                                    alert("AJAX ERROR---tbl_selctdprg!!");
                                }
                            });
                        }

                    },
                    error : function(err) {
                        alert("AJAX ERROR---tree_selctdprg!!");
                    }
                });
            }
        }
    });

    //右侧table
    globalObj._outtable = $('#tbl_outtable').dataTable( {
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

    $('#tbl_outtable tbody').on( 'click', 'tr', function () {
        $('#tbl_outtable').DataTable().$('tr.selected').removeClass('selected');
        $(this).addClass('selected');
        var index = $(this)[0].cells[0].textContent-1;
        $.ajax({
            type: "GET",
            async: false,
            url: "http://"+localip+":4000/do/programs/tbl_selctdprg?index="+index,
            dataType: "json",
            success: function(data){
                if(data.sts == 8){
                    window.location = "/login.esp";
                }
                if(data.outMode < 3){
                    $('.prg_outmode')[0].selectedIndex = 0;
                }else if(data.outMode == 3){
                    $('.prg_outmode')[0].selectedIndex = 1;
                }
                $('.prg_ch').val(index + 1);
                $('.prg_destip').val(data.ipStr);
                $('.prg_destport').val(data.port);
                $('.prg_destmac').val(data.macStr);

            },
            error : function(err) {
                alert("AJAX ERROR---tbl_selctdprg!!");
            }
        });
    } );

    $('.output_mode').on('change', function(){
        var spstindex = $('.output_mode')[0].selectedIndex;
        setIpTvmode(spstindex);
        if(spstindex){
            $('.input_spts').css("display", "block");
            $('#output-auto').css("display", "");
            $('#output-clear').css("display", "");
        }else{
            $('.input_spts').css("display", "none");
            $('#output-auto').css("display", "none");
            $('#output-clear').css("display", "none");
        }
        outprgList();
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
        if(isNaN($('.s_port').val())){
            alert("非法的端口号.");
        }else{
            if(parseInt($('.s_port').val())>65535 || parseInt($('.s_port').val()<0)){
                alert("端口号溢出.");
                return false;
            }
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



