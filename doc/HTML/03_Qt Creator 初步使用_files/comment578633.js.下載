define("pages/voice_tpl.html.js",[],function(){
return'<span class="js_audio_frame db pages_reset audio_area <#if(!!albumLink){#>audio_area_tag<#}#>">\n    <#if(show_not_support===true){#>\n    <span class="db">当前浏览器不支持播放音乐或语音，请在微信或其他浏览器中播放</span>\n    <#}#>\n    <!-- 无话题的时候点击倍数等播放区域外的卡片区域：audio_card加.appmsg_card_custom_active -->\n    <!-- 有话题的时候点击非话题区域，且倍数等播放区域外的卡片区域：audio_card加.appmsg_card_custom_active -->\n    <span aria-labelledby="语音" id="voice_main_<#=voiceid#>_<#=posIndex#>" class="appmsg_card_context db audio_card" <#if(!musicSupport){#>style="display:none;"<#}#>>\n      <span id="audio_card_bd_<#=voiceid#>_<#=posIndex#>" class="audio_card_bd">\n        <strong id="voice_title_<#=voiceid#>_<#=posIndex#>" class="audio_card_title" aria-describedby="语音标题" role="link"><#=title#></strong>\n\n        <!-- <#if(!!nickname){#>\n        <span id="voice_author_<#=voiceid#>_<#=posIndex#>" class="audio_card_desc">来自<#=nickname#></span>\n        <#}#> -->\n\n        <span class="weui-flex weui-flex_align-center">\n          <span class="weui-flex__item">\n            <span class="audio_card_opr">\n              <span id="voice_seekRange_<#=voiceid#>_<#=posIndex#>" class="audio_card_progress_wrp">\n                <span class="audio_card_progress">\n                  <span id="voice_progress_<#=voiceid#>_<#=posIndex#>" style="width:0%" class="audio_card_progress_inner"></span>\n                  <span id="voice_buffer_<#=voiceid#>_<#=posIndex#>" class="audio_card_progress_buffer" style="width:0%;"></span>\n                  <span id="voice_loading_<#=voiceid#>_<#=posIndex#>" class="audio_card_progress_loading" style="display:none;"></span>\n                </span>\n              <span id="voice_playdot_<#=voiceid#>_<#=posIndex#>" class="audio_card_progress_handle" style="display:none;left:0%;"></span>\n              </span>\n              <span class="audio_card_tips" aria-labelledby="时长">\n                <em id="voice_playtime_<#=voiceid#>_<#=posIndex#>" class="audio_card_length_current" aria-hidden="true">00:00</em>\n                <em id="voice_duration_<#=voiceid#>_<#=posIndex#>" class="audio_card_length_total"><#=duration_str#></em>\n              </span>\n            </span>\n          </span>\n          <span id="voice_play_<#=voiceid#>_<#=posIndex#>" aria-labelledby="播放开关" class="audio_card_switch"><em id="audio_play_btn" class="weui-audio-btn" role="button"></em></span>\n        </span>\n\n        <span id="audio_card_control_<#=voiceid#>_<#=posIndex#>" class="weui-flex weui-flex_align-center audio_card_playtool" style="display: none;">\n          <button type="button" id="audio_fast_back_<#=voiceid#>_<#=posIndex#>" class="reset_btn audio_card_playbtn"><span class="aria_hidden_abs">后退15秒</span></button>\n          <button type="button" id="audio_double_speed_<#=voiceid#>_<#=posIndex#>" class="weui-btn weui-btn_mini audio_card_playbtn_multiple">倍速</button>\n          <button type="button" id="audio_fast_forward_<#=voiceid#>_<#=posIndex#>" class="reset_btn audio_card_playbtn"><span class="aria_hidden_abs">快进15秒</span></button>\n        </span>\n      </span>\n\n      <#if(!!albumLink){#>\n      <span class="audio_card_ft">\n        <span role="link" id="voice_album_<#=voiceid#>_<#=posIndex#>" class="audio__tag" data-link="<#=albumLink#>" data-title="<#=albumTitle#>" data-album="<#=albumid#>" target="_blank">\n          <span class="audio__tag-title">话题</span>\n          <span class="weui-flex__item">\n            <span class="audio__tag-name">#<#=albumTitle#></span>\n          </span>\n          <span class="audio__tag-num"><#=albumNum#>个</span>\n        </span>\n      </span>\n      <#}#>\n    </span>\n</span>\n\n';
});define("pages/kugoumusic_ctrl.js",["biz_wap/utils/jsmonitor_report.js","biz_wap/utils/ajax.js","pages/musicUrlReport.js"],function(e){
"use strict";
function r(e,r){
for(var t,a=[/^http(s)?:\/\/singerimg\.kugou\.com([\/?].*)*$/i,/^http(s)?:\/\/imge\.kugou\.com([\/?].*)*$/i],o=!1,s=0;t=a[s++];)if(t.test(e.albumurl)){
o=!0;
break;
}
return o||(e.albumurl=""),e.detailUrl="https://m3ws.kugou.com/kgsong/"+e.jumpurlkey+".html?fromweixin=",
e.webUrl=e.detailUrl,e.musicIcon=n.musicIcon,e.media_id=e.musicid,e.type=1*r.scene===0?5:1*r.scene===1?6:9,
e;
}
function t(e,r){
var t=e,a=t.otherid+(t.albumid||""),s=n.cache[a];
return s&&"function"==typeof r.callback?void r.callback(s):void(n.submiting[a]!==!0&&(n.submiting[a]=!0,
o({
jumpurlkey:t.jumpurlkey,
songId:t.songId,
akey:t.otherid,
albumid:t.albumid||"",
onSuc:function(e){
n.submiting[a]=!1,n.cache[a]=e,"function"==typeof r.callback&&r.callback(e);
},
onError:function(){
n.submiting[a]=!1,"function"==typeof r.callback&&r.callback({
canplay:!1,
msg:"系统繁忙，请稍后再试。返回码：-1",
status:-1,
play_url:"",
duration:0
});
}
})));
}
function a(e){
var r=!0,t="";
switch(1*e){
case 0:
r=!0;
break;

case 1:
r=!1,t="该歌曲版权已过期，无法播放。";
break;

case 1002:
r=!1,t="系统错误，请稍后再试。";
break;

case 1001:
r=!1,t="系统错误，请稍后再试。";
break;

default:
r=!1,t="系统错误，请稍后再试。";
}
return t&&(t+="错误码："+e),{
canplay:r,
msg:t
};
}
function o(e){
u.setSum(n.reportId,87,1);
var r=+new Date,t="/mp/getkugousong?params=#params#",o=[{
akey:e.akey,
albumid:e.albumid||""
}],m=encodeURIComponent(JSON.stringify(o));
t=t.replace("#params#",m),c({
url:t,
type:"GET",
dataType:"json",
success:function(t){
var o=+new Date-r;
if(setTimeout(function(){
i.reportRespData({
type:2,
songid:e.songId,
musicid:e.akey,
jumpurlkey:e.jumpurlkey,
responseData:JSON.stringify(t||{}),
kugouParams:m
});
},0),!t||"undefined"==typeof t.errcode){
var u=1;
return s({
type:"error",
time:o,
code:u
}),void("function"==typeof e.onError&&e.onError({
errcode:u
}));
}
var c=0,n="";
0==t.errcode?t.data&&t.data[0]&&t.data[0].url?(c=0,n=t.data[0].url):c=1001:c=1==t.errcode?1:1002,
s({
type:"success",
time:o,
code:c
});
var p=a(c);
e.onSuc({
canplay:p.canplay,
msg:p.msg,
errcode:c,
play_url:n
});
},
error:function(){
var t=+new Date-r,a=2;
s({
type:"error",
time:t,
code:a
}),"function"==typeof e.onError&&e.onError({
errcode:a
});
}
});
}
function s(e){
var r=Math.max(e.time,0);
if(r=Math.min(r,1e4),r>=0&&500>r?u.setSum(n.reportId,98,1):r>=500&&1e3>r?u.setSum(n.reportId,99,1):r>=1e3&&2e3>r?u.setSum(n.reportId,100,1):r>=2e3&&5e3>r?u.setSum(n.reportId,101,1):r>=5e3&&1e4>=r&&u.setSum(n.reportId,102,1),
"error"==e.type){
switch(1*e.code){
case 1:
u.setSum(n.reportId,94,1);
break;

case 2:
u.setSum(n.reportId,91,1);
break;

case 3:
u.setSum(n.reportId,92,1);
break;

case 4:
u.setSum(n.reportId,93,1);
}
u.setSum(n.reportId,88,1);
}else if("success"==e.type){
switch(1*e.code){
case 1:
u.setSum(n.reportId,95,1);
break;

case 0:
u.setSum(n.reportId,97,1);
break;

case 1002:
u.setSum(n.reportId,96,1);
break;

case 1001:
u.setSum(n.reportId,103,1);
}
u.setSum(n.reportId,89,1);
}
}
var u=e("biz_wap/utils/jsmonitor_report.js"),c=e("biz_wap/utils/ajax.js"),i=e("pages/musicUrlReport.js"),n={
reportId:"28306",
musicIcon:window.icon_kugou_source||"",
cache:{},
submiting:{}
};
return{
initData:r,
getPlayUrl:t
};
});define("pages/qqmusic_ctrl.js",["biz_wap/utils/jsmonitor_report.js","pages/player_adaptor.js","biz_wap/jsapi/log.js","biz_wap/utils/ajax.js","pages/musicUrlReport.js"],function(e){
"use strict";
function r(e,r){
if(/^http(s)?:\/\//i.test(e.albumurl)){
for(var t,a=[/^http(s)?:\/\/imgcache\.qq\.com([\/?].*)*$/i,/^http(s)?:\/\/y\.gtimg\.cn([\/?].*)*$/i],s=!1,i=0;t=a[i++];)if(t.test(e.albumurl)){
s=!0;
break;
}
s||(e.albumurl="");
}else{
var o=e.albumurl.split("/");
try{
o=o[o.length-1],o=o.split(".")[0];
}catch(n){
o="";
}
e.albumurl=o?m.imgroot2.replace("#mid#",o):m.imgroot+e.albumurl;
}
return e.albumurl=e.albumurl.replace("mid_album_68","mid_album_90").replace("68x68","90x90"),
e.musicIcon=m.musicIcon,e.type=1*r.scene===0?0:1*r.scene===1?1:8,c.inQMClient?(e.allowPause=!0,
e.detailUrl="",e.pauseCss="qqmusic_playing_pause",e.webUrl=e.detailUrl):(e.allowPause=!1,
e.pauseCss="",e.detailUrl=["http://i.y.qq.com/v8/playsong.html?referFrom=music.qq.com&songid=",e.musicid,"&songmid=",e.media_id,,"&ADTAG=weixin_gzh#wechat_redirect"].join(""),
e.webUrl=e.detailUrl),e;
}
function t(e,r){
var t=e,a=m.cache[t.songId];
return c.inQMClient?void r.callback({
canplay:!0,
play_url:"https://www.qq.com"
}):a&&"function"==typeof r.callback&&(a.canplay||!a.canplay&&!a.retry)?(a.in_cache=!0,
void r.callback(a)):void(m.submiting[t.songId]!==!0&&(m.submiting[t.songId]=!0,a&&o.setSum(m.reportId,122,1),
s({
id:t.songId,
mid:t.mid,
onSuc:function(e){
m.submiting[t.songId]=!1,m.cache[t.songId]&&!m.cache[t.songId].canplay&&e.canplay&&o.setSum(m.reportId,123,1),
m.cache[t.songId]=e,"function"==typeof r.callback&&r.callback(e);
},
onError:function(){
m.submiting[t.songId]=!1,"function"==typeof r.callback&&r.callback({
canplay:!1,
msg:"系统繁忙，请稍后再试。",
status:-1,
play_url:"",
duration:0
});
}
})));
}
function a(e){
var r=!0,t=!1,a="";
switch(1*e){
case 0:
r=!0;
break;

case 1:
r=!1,a="因版权限制，音乐无法播放。";
break;

case 2:
r=!1,a="因版权限制，音乐无法播放。";
break;

case 3:
r=!1,a="因版权限制，音乐无法播放。";
break;

case 4:
r=!1,a="当前区域因版权限制，音乐无法播放。";
break;

case 5:
r=!1,t=!0,a="播放失败，请稍后再试。";
break;

case 6:
r=!1,t=!0,a="系统错误，请稍后再试。";
break;

case 7:
r=!1,t=!0,a="系统错误，请稍后再试。";
break;

case 8:
r=!0,a="该音乐为付费音乐，当前为你播放试听片段。";
break;

default:
r=!1,a="系统错误，请稍后再试。";
}
return{
canplay:r,
msg:a,
retry:t
};
}
function s(e){
o.setSum(m.reportId,18,1);
var r=+new Date,t="//mp.weixin.qq.com/mp/qqmusic?action=get_song_info&song_mid=#mid#";
t=t.replace("#mid#",e.mid),p({
url:t,
type:"GET",
dataType:"json",
success:function(t){
var s=+new Date-r;
if(200==t.http_code){
setTimeout(function(){
u.reportRespData({
type:1,
songid:e.id,
musicid:e.mid,
responseData:t.resp_data||""
});
},0);
var o={};
try{
o=JSON.parse(t.resp_data);
}catch(c){
var p=1;
return i({
type:"error",
time:s,
code:p
}),"function"==typeof e.onError&&e.onError({
errcode:p
}),void n.info("qqmusic_checkCopyright_parsefail mid:"+e.mid+", repsponeData:"+t.resp_data);
}
if("undefined"==typeof o.ret||0!=o.ret||0!=o.sub_ret||0==o.songlist.length){
var p=1;
return i({
type:"error",
time:s,
code:p
}),"function"==typeof e.onError&&e.onError({
errcode:p
}),void n.info("qqmusic_checkCopyright_dataerror mid:"+e.mid+", repsponeData:"+t.resp_data);
}
var m,l=o.songlist[0],d=l.song_play_url,b=l.song_play_time||0;
if(l.playable)m=d?0:6;else if(l.try_playable)l.try_file_size>0&&l.try_30s_url?(m=8,
d=l.try_30s_url,b=30):m=7;else switch(1*l.unplayable_code){
case 1:
m=1;
break;

case 2:
m=2;
break;

case 3:
m=3;
break;

case 4:
m=4;
break;

case 5:
m=5;
break;

default:
m=5;
}
i({
type:"success",
time:s,
code:m
});
var y=a(1*m);
e.onSuc({
canplay:y.canplay,
retry:y.retry,
msg:y.msg,
status:m,
play_url:d||"",
duration:b
}),y.canplay||n.info("qqmusic_checkCopyright_cannotplay mid:"+e.mid+", repsponeData:"+t.resp_data);
}else{
var p=4;
switch(t.http_code){
case 200:
break;

case 400:
p=2;
break;

case 500:
p=3;
break;

default:
p=4;
}
i({
type:"error",
time:s,
code:p
}),"function"==typeof e.onError&&e.onError({
errcode:p
});
}
},
error:function(){
"function"==typeof e.onError&&e.onError({
errcode:4
});
}
});
}
function i(e){
var r=Math.max(e.time,0);
if(r=Math.min(r,6e4),e.time>=0&&e.time<200?o.setSum(m.reportId,24,1):e.time>=200&&e.time<500?o.setSum(m.reportId,25,1):e.time>=500&&e.time<1e3?o.setSum(m.reportId,26,1):e.time>=1e3&&e.time<2e3?o.setSum(m.reportId,27,1):e.time>=2e3&&e.time<1e4?o.setSum(m.reportId,28,1):e.time>=1e4&&o.setSum(m.reportId,29,1),
o.setAvg(m.reportId,23,r),"error"==e.type){
switch(1*e.code){
case 1:
o.setSum(m.reportId,9,1);
break;

case 2:
o.setSum(m.reportId,10,1);
break;

case 3:
o.setSum(m.reportId,11,1);
break;

case 4:
o.setSum(m.reportId,12,1);
}
o.setSum(m.reportId,19,1);
}else if("success"==e.type){
switch(1*e.code){
case 1:
o.setSum(m.reportId,8,1);
break;

case 0:
o.setSum(m.reportId,17,1);
break;

case 2:
o.setSum(m.reportId,13,1);
break;

case 3:
o.setSum(m.reportId,14,1);
break;

case 4:
o.setSum(m.reportId,15,1);
break;

case 5:
o.setSum(m.reportId,16,1);
break;

case 6:
o.setSum(m.reportId,47,1);
break;

case 7:
o.setSum(m.reportId,120,1);
break;

case 8:
o.setSum(m.reportId,121,1);
}
o.setSum(m.reportId,20,1);
}
}
var o=e("biz_wap/utils/jsmonitor_report.js"),c=e("pages/player_adaptor.js"),n=e("biz_wap/jsapi/log.js"),p=e("biz_wap/utils/ajax.js"),u=e("pages/musicUrlReport.js"),m={
imgroot:"https://imgcache.qq.com/music/photo/mid_album_90",
imgroot2:"https://y.gtimg.cn/music/photo_new/T002R90x90M000#mid#.jpg",
reportId:"28306",
musicIcon:window.icon_qqmusic_source||"",
cache:{},
submiting:{}
};
return{
initData:r,
getPlayUrl:t
};
});var _extends=Object.assign||function(e){
for(var t=1;t<arguments.length;t++){
var a=arguments[t];
for(var o in a)Object.prototype.hasOwnProperty.call(a,o)&&(e[o]=a[o]);
}
return e;
};
define("pages/voice_component.js",["biz_wap/zepto/zepto.js","biz_common/dom/event.js","biz_common/tmpl.js","pages/music_player.js","pages/player_adaptor.js","biz_common/dom/class.js","pages/report.js","pages/music_report_conf.js","pages/player_tips.js","biz_wap/jsapi/leaveReport.js","biz_wap/utils/mmversion.js","biz_wap/utils/ajax.js","biz_wap/utils/openUrl.js","pages/qqmusic_ctrl.js","pages/kugoumusic_ctrl.js","album/utils/report.js","common/comm_report.js"],function(e){
"use strict";
function t(){
j.hasInit||(i(),n(),p(),j.hasInit=!0);
}
function a(e){
t(),this._o={
protocal:"",
wxIndex:0,
type:0,
comment_id:"",
src:"",
jsapi2Src:"",
mid:"",
songId:"",
otherid:"",
albumid:"",
jumpurlkey:"",
autoPlay:!1,
duration:0,
needVioceMutex:!0,
appPlay:!0,
title:"",
allowPause:!1,
singer:"",
epname:"",
coverImgUrl:"",
webUrl:[location.protocol,"//mp.weixin.qq.com/s?referFrom=#referFrom#&songid=#songId#&__biz=",window.biz,"&mid=",window.mid,"&idx=",window.idx,"&sn=",window.sn,"#wechat_redirect"].join(""),
musicbar_url:"",
playingCss:"",
pauseCss:"",
playCssDom:"",
playArea:"",
progress:"",
detailUrl:"",
detailArea:"",
fileSize:0,
playtimeDom:"",
loadingDom:"",
bufferDom:"",
playdotDom:"",
seekRange:"",
seekContainer:""
},this._init(e),j.allComponent.push(this);
}
function o(e){
if(!e.isReport){
var t=(e.getAttribute("data-link"),$(e).parent().parent().siblings()),a=$(e).data("album"),o=t.attr("voice_encode_fileid"),r=$(e).data("title");
e.isReport=1,P.cardReport({
albumId:a,
albumType:7,
eventType:1,
audioid:o,
title:r
});
}
}
function r(e,t,a,o){
j.num++,t.musicSupport=j.musicSupport,t.show_not_support=!1,j.musicSupport||1!=j.num||(t.show_not_support=!0);
var r=document.createElement("div"),n="";
if(n=m.tmpl(e,t,!1),r.innerHTML=n,o===!0)a.appendChild(r.children[0]);else{
var i=a.parentNode;
if(!i)return;
i.lastChild===a?i.appendChild(r.children[0]):i.insertBefore(r.children[0],a.nextSibling);
}
}
function n(){
j.hasInit||h.inQMClient&&s("QMClient_pv",1);
}
function i(){
window.reportMid=[],window.reportVoiceid=[];
for(var e in w)if(w.hasOwnProperty(e)){
var t=w[e],a=t.split("_");
j.reportData2[e]={
id:a[0],
key:a[1],
count:0
};
}
}
function s(e,t){
j.reportData2[e]&&(t=t||1,j.reportData2[e].count+=t,j.debug&&console.log("addpv:"+e+" count:"+j.reportData2[e].count));
}
function p(){
I.gtVersion("7.0.6")||y.on(window,"unload",function(){
for(var e=l(),t=JSON.parse(e.report_list),a=0;a<t.length;a++)x({
type:"POST",
url:"/mp/musicreport?#wechat_redirect",
timeout:2e4,
async:!0,
data:t[a]
});
}),j.repotIntervalId&&clearInterval(j.repotIntervalId),j.repotIntervalId=setInterval(function(){
c();
},3e4);
}
function l(){
f.triggerUnloadPlaying(),c();
for(var e,t={},a=0,o=j.allComponent.length;o>a;a++){
var r=j.allComponent[a];
r.player&&"function"==typeof r.player.getPlayTotalTime&&(j.reportData[r._o.type].play_last_time[r._g.posIndex]=parseInt(1e3*r.player.getPlayTotalTime())),
"number"!=typeof r._status||1!==r._status&&4!==r._status||(e=r._o.songId);
}
e&&(t.current_musicid=e);
var n=[];
for(var a in j.reportData)n=n.concat(D.musicreport({
data:j.reportData[a]
}));
t.report_list=JSON.stringify(n),i();
for(var a=0,o=j.allComponent.length;o>a;a++){
var r=j.allComponent[a];
r&&"function"==typeof r._initReportData&&r._initReportData(),r.player&&"function"==typeof r.player.resetPlayTotalTime&&r.player.resetPlayTotalTime();
}
return t;
}
function c(){
var e=[];
for(var t in j.reportData2)if(j.reportData2.hasOwnProperty(t)){
var a=j.reportData2[t];
a.count>0&&(e.push(a.id+"_"+a.key+"_"+a.count),a.count=0);
}
e.length>0&&x({
type:"POST",
url:"/mp/jsmonitor?#wechat_redirect",
timeout:2e4,
async:!1,
data:{
idkey:e.join(";"),
t:Math.random()
}
});
}
function d(e){
return new a(e);
}
function u(e){
if(isNaN(e))return"00:00";
e=Math.floor(e);
var t=Math.floor(e/3600),a=Math.floor((e-3600*t)/60),o=e-3600*t-60*a;
return 0!=t?(10>t&&(t="0"+t),t+=":"):t="",10>a&&(a="0"+a),10>o&&(o="0"+o),t+a+":"+o;
}
function _(e){
return e=(e||"").replace(/&#96;/g,"`").replace(/&#61;/g,"=").replace(/&#39;/g,"'").replace(/&quot;/g,'"').replace(/&lt;/g,"<").replace(/&gt;/g,">").replace(/&amp;/g,"&");
}
function g(e){
return e=(e||"").replace(/&/g,"&amp;").replace(/>/g,"&gt;").replace(/</g,"&lt;").replace(/"/g,"&quot;").replace(/'/g,"&#39;").replace(/=/g,"&#61;").replace(/`/g,"&#96;");
}
e("biz_wap/zepto/zepto.js");
var y=e("biz_common/dom/event.js"),m=e("biz_common/tmpl.js"),f=e("pages/music_player.js"),h=e("pages/player_adaptor.js"),v=e("biz_common/dom/class.js"),D=e("pages/report.js"),w=e("pages/music_report_conf.js"),b=e("pages/player_tips.js"),k=e("biz_wap/jsapi/leaveReport.js"),I=e("biz_wap/utils/mmversion.js"),x=e("biz_wap/utils/ajax.js"),C=e("biz_wap/utils/openUrl.js").openUrlWithExtraWebview,j={
allComponent:[],
hasInit:!1,
reportId:"28306",
musicSupport:f.getSurportType(),
debug:location.href.indexOf("vconsole=1")>0||document.cookie&&document.cookie.indexOf("vconsole_open=1")>-1?!0:!1,
reportData:{},
posIndex:{},
num:0,
reportData2:{},
adapter:{
m:e("pages/qqmusic_ctrl.js"),
k:e("pages/kugoumusic_ctrl.js")
},
needReport11982:!1,
repotIntervalId:null,
inWechat:I.isWp||/MicroMessenger/.test(window.navigator.userAgent),
inPC:I.isWindows||I.isMac&&!I.isIOS,
fastForwardSec:15,
fastBackSec:15
},P=e("album/utils/report.js"),S=e("common/comm_report.js"),B=null;
return"function"==typeof IntersectionObserver&&(B=new IntersectionObserver(function(e){
e.forEach(function(e){
e.isIntersecting&&o(e.target);
});
})),a.prototype._init=function(e){
this._extend(e),this._g={
posIndex:void 0,
tag:"",
canDragBar:!1,
barDraging:!1,
canGoDetail:!0
},5==this._o.type||6==this._o.type||9==this._o.type?this._g.tag="k":this._o.type>=2&&this._o.type<=4?this._g.tag="v":7==this._o.type?this._g.tag="a":(0==this._o.type||1==this._o.type||8==this._o.type)&&(this._g.tag="m"),
this._initData(),this._initQQmusicLyric(),this._initReportData(),this._initPlayer();
},a.prototype._initData=function(){},a.prototype._initQQmusicLyric=function(){
var e=this._o,t=this._g;
e.webUrl="m"==t.tag?e.webUrl.replace("#songId#",e.songId||"").replace("#referFrom#","music.qq.com"):e.webUrl.replace("#songId#","").replace("#referFrom#","");
},a.prototype._initReportData=function(){
var e=this._o,t=this._g;
"v"==t.tag?window.reportVoiceid.push(e.songId):"m"==t.tag&&window.reportMid.push(e.songId),
"undefined"==typeof j.reportData[e.type]&&(j.reportData[e.type]=D.getMusicReportData(e),
j.posIndex[e.type]=0),"undefined"==typeof t.posIndex&&(t.posIndex=j.posIndex[e.type]++);
var a=j.reportData[e.type];
a.musicid[t.posIndex]=e.songId,a.commentid[t.posIndex]=e.comment_id,a.hasended[t.posIndex]=0,
a.mtitle[t.posIndex]=e.title,a.detail_click[t.posIndex]=0,a.duration2[t.posIndex]=parseInt(1e3*e.duration),
a.errorcode[t.posIndex]=0,a.play_duration2[t.posIndex]=0,a.seek[t.posIndex]=0,a.seek_position[t.posIndex]=[],
a.play_last_time[t.posIndex]=0,a.local_time[t.posIndex]=0,a.seek_loaded[t.posIndex]=[];
},a.prototype._initPlayer=function(){
if(j.musicSupport){
var e=this,t=this._o,a=this._g.tag;
t.onStatusChange=this._statusChangeCallBack(),t.onTimeupdate=this._timeupdateCallBack(),
t.onError=this._errorCallBack(),t.onUpdateSeekRange=this._onUpdateSeekRange(),t.onAndroidForceH5=function(){
s("force_h5",1);
},t.onH5Begin2Play=function(){
s(a+"_pv",1),s(a+"_h5_pv",1);
},t.onH5Error=function(t,o){
s(a+"_h5_err_total",1),s(a+"_h5_err_"+o.code,1),e._reportH5Error({
type:1,
code:o.code
});
},t.onJsapi1Begin2Play=function(){
s(a+"_pv",1),s(a+"_wx_pv",1),s(a+"_wx_pv_1",1);
},t.onJsapi2Begin2Play=function(e,o){
s(a+"_pv",1),s(a+"_wx_pv",1),s(a+"_wx_pv_2",1),t.jsapi2Src&&t.jsapi2Src!=t.src&&s("aac_pv",1),
t.musicPlayerOnJsapi2Begin2Play&&t.musicPlayerOnJsapi2Begin2Play(o);
},t.onJsapi2PlaySuccess=function(e,a){
t.musicPlayerOnJsapi2PlaySuccess&&t.musicPlayerOnJsapi2PlaySuccess(a);
},t.onJsapi2Begin2PlayErr=function(){
if(s(a+"_wx_err_1",1),t.jsapi2Src&&t.jsapi2Src!=t.src){
var e="acc_start_error;type:#type#;uin:"+(window.user_uin||"")+";playurl:"+t.jsapi2Src+";pageurl:"+location.href;
f.isAndroid?(D.logReport("",e.replace("#type#","android"),"ajax"),s("android_aac_err_1",1)):(D.logReport("",e.replace("#type#","ios"),"ajax"),
s("ios_aac_err_1",1));
}
},t.onJsapi2PlayingErr=function(){
if(s(a+"_wx_err_2",1),t.jsapi2Src&&t.jsapi2Src!=t.src){
var e="acc_ing_error;type:#type#;uin:"+(window.user_uin||"")+";playurl:"+t.jsapi2Src+";pageurl:"+location.href;
f.isAndroid?(D.logReport("",e.replace("#type#","android"),"ajax"),s("android_aac_err_2",1)):(D.logReport("",e.replace("#type#","ios"),"ajax"),
s("ios_aac_err_2",1));
}
},t.onJsapi2PlayingStop=function(){
var e=a+"_stoped_";
e+=f.isAndroid?"android":"ios",s(e,1);
},t.onJsapi2PlayingPause=function(){
var e=a+"_paused_";
e+=f.isAndroid?"android":"ios",s(e,1);
},t.onSeekErr=function(){
if(s(a+"_seek_err",1),t.jsapi2Src&&t.jsapi2Src!=t.src){
var e="acc_seek_error;type:#type#;uin:"+(window.user_uin||"")+";playurl:"+t.jsapi2Src+";pageurl:"+location.href;
f.isAndroid?(D.logReport("",e.replace("#type#","android"),"ajax"),s("android_aac_err_3",1)):(D.logReport("",e.replace("#type#","ios"),"ajax"),
s("ios_aac_err_3",1));
}
},t.onUnloadPlaying=function(){
s(a+"_unload_wx_pv",1);
},t.onQMClientPlay=function(){
s("QMClient_play",1);
},t.onSeekNeed2Load=function(){
if(e.player&&e.player.surportSeekRange()&&t.playdotDom){
var a=j.reportData[e._o.type],o=a.seek_position[e._g.posIndex].length;
o>0&&(a.seek_loaded[e._g.posIndex][o-1]=1);
}
},t.onSeekNotNeed2Load=function(){
if(e.player&&e.player.surportSeekRange()&&t.playdotDom){
var a=j.reportData[e._o.type],o=a.seek_position[e._g.posIndex].length;
o>0&&(a.seek_loaded[e._g.posIndex][o-1]=0);
}
},h.create(this._o,{
callback:function(t){
e.player=t,e.afterCreatePlayer();
}
});
}
},a.prototype.afterCreatePlayer=function(){
this._playEvent();
},a.prototype.isInSeekrang=function(e){
var t=this._o.seekRange;
if(!t)return!1;
if(t===e)return!0;
for(var a=t.getElementsByTagName("*"),o=0,r=a.length;r>o;o++)if(a[o]===e)return!0;
return!1;
},a.prototype._playEvent=function(){
var e=this,t=this._o,a=this._g,o=function(e){
if("[object String]"!==Object.prototype.toString.call(e))return!1;
var t=["audio_fast_back","audio_double_speed","audio_fast_forward","audio_play_btn"];
return t.some(function(t){
return-1!==e.indexOf(t);
});
};
if(t.detailUrl&&t.detailArea&&(y.on(t.detailArea,"click",function(r){
if(!o(r.target.getAttribute("id"))&&!a.barDraging&&a.canGoDetail){
var n=r.target||r.srcElement;
n&&e.isInSeekrang(n)||("v"==a.tag?(j.reportData[t.type].detail_click[a.posIndex]=1,
window.__second_open__?C(t.detailUrl):window.location.href=t.detailUrl):("m"==a.tag||"k"==a.tag)&&j.adapter[a.tag].getPlayUrl(t,{
callback:function(e){
e.canplay?(j.reportData[t.type].detail_click[a.posIndex]=1,window.__second_open__?C(t.detailUrl):window.location.href=t.detailUrl):e.msg&&new b({
msg:e.msg
});
}
}));
}
}),t.audioCardBody&&(j.inWechat?(y.on(t.audioCardBody,"touchstart",function(e){
o(e.target.getAttribute("id"))||t.detailArea.classList.add("appmsg_card_custom_active");
}),y.on(t.audioCardBody,"touchend",function(e){
o(e.target.getAttribute("id"))||t.detailArea.classList.remove("appmsg_card_custom_active");
})):j.inPC&&(y.on(t.audioCardBody,"mousedown",function(e){
o(e.target.getAttribute("id"))||t.detailArea.classList.add("appmsg_card_custom_active");
}),y.on(t.audioCardBody,"mouseup",function(e){
o(e.target.getAttribute("id"))||t.detailArea.classList.remove("appmsg_card_custom_active");
})))),t.albumDom&&(B&&B.observe(t.albumDom),y.on(t.albumDom,"click",function(){
var e=t.albumDom.getAttribute("data-link").replace("#wechat_redirect","&scene=173#wechat_redirect"),a=$(t.albumDom).parent().parent().siblings(),o=$(t.albumDom).data("album"),r=a.attr("voice_encode_fileid"),n=$(t.albumDom).data("title");
return P.cardReport({
albumId:o,
albumType:7,
eventType:2,
audioid:r,
title:n
}),C(e),!1;
},!0)),j.musicSupport){
var r=0,n=4,i=5;
switch(1*t.type){
case 0:
r=1;
break;

case 1:
r=13;
break;

case 8:
r=14;
break;

case 2:
r=3;
break;

case 3:
r=6;
break;

case 4:
r=7;
break;

case 5:
r=10;
break;

case 6:
r=15;
break;

case 7:
r=11;
break;

case 9:
r=12;
}
var s="";
s=t.allowPause?t.pauseCss||t.playingCss:t.playingCss,y.tap(t.playArea,function(){
return console.log("click playArea",v.hasClass(t.playCssDom,s)),v.hasClass(t.playCssDom,s)?(t.allowPause?e.player.pause():e.player.stop(),
D.report({
type:r,
comment_id:t.comment_id,
voiceid:t.songId,
action:i
})):"v"==a.tag||"a"==a.tag?e._playMusic(r,n):j.adapter[a.tag].getPlayUrl(t,{
callback:function(o){
o.canplay&&o.play_url?(o.duration&&(t.duration=o.duration,e.player.setDuration(t.duration),
j.reportData[t.type].duration2[a.posIndex]=parseInt(1e3*t.duration)),e.player.setSrc(o.play_url),
8!=o.status||o.in_cache?e._playMusic(r,n):new b({
msg:"该音乐为付费音乐，当前为你播放试听片段",
onClick:function(){
e._playMusic(r,n);
}
})):o.msg&&new b({
msg:o.msg
});
}
}),!1;
}),e._dragEvent(),e._ctrlAreaEvt();
}
},a.prototype.getSeekRangeOffsetLeft=function(){
var e=0,t=this._o.seekRange,a=!1,o=window.__zoom||1;
for(1!=o&&(a=!0);t&&t!=document.body;)e+=a?t.offsetLeft*o:t.offsetLeft,"page-content"==t.id&&(a=!1),
t=t.offsetParent;
return e;
},a.prototype._dragEvent=function(){
var e=this,t=this._o,a=this._g,o=t.seekRange;
if(o){
var r=e.player.getDuration();
a.seekData={
zoom:window.__zoom||1,
duration:r,
startTime:0,
dragTime:0,
downX:0,
moveX:0
},y.on(o,"mousedown",function(t){
a.canDragBar&&(e._pointerDownHandler({
x:t.pageX||t.clientX
}),t.preventDefault(),t.stopPropagation());
}),y.on(t.seekContainer,"mousemove",function(t){
a.canDragBar&&a.barDraging&&(e._pointerMoveHandler({
x:t.pageX||t.clientX
}),t.preventDefault(),t.stopPropagation());
}),y.on(document.body,"mouseup",function(t){
return a.canDragBar&&a.barDraging?(e._pointerUpHandler({
x:t.pageX||t.clientX
}),t.preventDefault(),t.stopPropagation(),!1):void 0;
}),y.on(o,"touchstart",function(t){
a.canDragBar&&(e._pointerDownHandler({
x:t.changedTouches[0].clientX
}),t.preventDefault(),t.stopPropagation());
}),y.on(o,"touchmove",function(t){
a.canDragBar&&a.barDraging&&(e._pointerMoveHandler({
x:t.changedTouches[0].clientX
}),t.preventDefault(),t.stopPropagation());
}),y.on(o,"touchend",function(t){
return a.canDragBar&&a.barDraging?(e._pointerUpHandler({
x:t.changedTouches[0].clientX
}),t.preventDefault(),t.stopPropagation(),!1):void 0;
});
}
},a.prototype._ctrlAreaEvt=function(){
var e=this,t=this._o;
t.fastBackBtn&&y.tap(t.fastBackBtn,function(){
var t=e.player.getCurTime(),a=Math.max(+t-j.fastBackSec,0);
e.player.seek(a),e.report11899({
Action:33
});
}),t.fastForwardBtn&&y.tap(t.fastForwardBtn,function(){
var t=e.player.getCurTime(),a=e.player.getDuration(),o=Math.min(+t+j.fastForwardSec,+a);
e.player.seek(o),e.report11899({
Action:32
});
}),t.doubleSpeedBtn&&y.tap(t.doubleSpeedBtn,function(){
var a=f.getPlaybackRate();
e.player.doubleSpeed({
succCallback:function(){
var t=f.getPlaybackRate();
e.report11899({
Action:21,
FromPlaybackRate:a+"",
ToPlaybackRate:t+""
});
},
pcCallback:function(){
var e=f.getPlaybackRate();
t.doubleSpeedBtn.innerHTML=1===e?"倍速":e+"倍";
}
});
});
},a.prototype._pointerDownHandler=function(e){
var t=this._g;
t.barDraging=!0,t.canGoDetail=!1,t.seekData.downX=e.x,t.seekData.startTime=this.player.getCurTime();
},a.prototype._pointerMoveHandler=function(e){
var t=this._g,a=t.seekData;
a.moveX=e.x;
var o=this.getSeekRangeOffsetLeft(),r=(a.moveX-o)/a.zoom/this._o.seekRange.offsetWidth;
r=Math.min(r,1),r=Math.max(r,0),a.dragTime=r*a.duration,a.dragTime!=a.startTime&&this._updateProgressBar(a.dragTime);
},a.prototype._pointerUpHandler=function(e){
var t=this._g,a=t.seekData;
a.dragTime||this._pointerMoveHandler({
x:e.x
}),t.barDraging=!1,this.player.seek(a.dragTime),j.reportData[this._o.type].seek[t.posIndex]=1,
j.reportData[this._o.type].seek_position[t.posIndex].push(parseInt(1e3*a.startTime)+","+parseInt(1e3*a.dragTime));
var o=j.reportData[this._o.type].seek_position[t.posIndex].length;
j.reportData[this._o.type].seek_loaded[t.posIndex][o-1]=0,t.seekData.startTime=0,
t.seekData.dragTime=0,t.seekData.downX=0,t.seekData.moveX=0,setTimeout(function(){
t.canGoDetail=!0;
},1e3);
},a.prototype._playMusic=function(e,t){
var a=this._o,o=this._g;
this.player.play(),j.reportData[a.type].hasended[o.posIndex]=1,0==j.reportData[a.type].local_time[o.posIndex]&&(j.reportData[a.type].local_time[o.posIndex]=parseInt(+new Date/1e3)),
D.report({
type:e,
comment_id:a.comment_id,
voiceid:a.songId,
action:t
}),I.gtVersion("7.0.6")&&!j.needReport11982&&(j.needReport11982=!0,k.addSpecificReport("music_data",l),
console.log("music play leave report added"));
},a.prototype._extend=function(e){
for(var t in e)this._o[t]=e[t];
},a.prototype._onUpdateSeekRange=function(){
var e=this,t=e._o,a=e._g;
return function(e){
this.surportSeekRange()&&t.bufferDom&&t.playdotDom?(a.canDragBar=!0,t.playdotDom.style.display="block",
t.bufferDom.style.width=1*e+"%"):(a.canDragBar=!1,t.playdotDom&&(t.playdotDom.style.display="none"));
};
},a.prototype._statusChangeCallBack=function(){
var e=this;
return function(t,a){
e._status=a,e._updatePlayerCss(this,a),e._o.musicPlayerStatusChange&&e._o.musicPlayerStatusChange(a);
};
},a.prototype._timeupdateCallBack=function(){
var e=this,t=this._o,a=this._g;
return function(o,r){
e._updateProgress(r),0!=r&&(j.reportData[t.type].play_duration2[a.posIndex]=parseInt(1e3*r)),
e._o.timeupdateCallBack&&e._o.timeupdateCallBack(r);
};
},a.prototype._errorCallBack=function(){
var e=this,t=this._o,a=this._g;
return function(o,r){
j.reportData[t.type].errorcode[a.posIndex]=r.code,e._updatePlayerCss(this,3);
};
},a.prototype._reportH5Error=function(e){
if("mp.weixin.qq.com"==location.host&&1==e.type||j.debug){
var t=["code:",e.code,";type:",this._o.type,";url:",window.location.href];
this.player&&t.push(";src:"+this.player.getSrc());
var a=new Image;
a.src=["https://badjs.weixinbridge.com/badjs?level=4&id=112&msg=",encodeURIComponent(t.join("")),"&uin=",window.uin||"","&from=",this._o.type].join("");
}
},a.prototype._updatePlayerCss=function(e,t){
!!j.debug&&console.log("status:"+t);
{
var a=this,o=a._o,r=o.playCssDom;
o.progress;
}
if(2===t)v.removeClass(r,o.playingCss),o.pauseCss&&v.removeClass(r,o.pauseCss),o.playdotDom&&(e.surportSeekRange()?(o.playdotDom.style.display="block",
this._g.canDragBar=!0):(o.playdotDom.style.display="none",this._g.canDragBar=!1));else if(3===t)o.ctrlArea&&(o.ctrlArea.style.display="none"),
v.removeClass(r,o.playingCss),o.pauseCss&&v.removeClass(r,o.pauseCss),o.playdotDom&&(o.playdotDom.style.display="none",
this._g.canDragBar=!1),this._updateProgress(0);else if(1===t||4===t){
var n=f.getPlaybackRate();
o.doubleSpeedBtn&&(o.doubleSpeedBtn.innerHTML=1===n?"倍速":n+"倍"),j.allComponent.forEach(function(e){
e===a?o.ctrlArea&&(o.ctrlArea.style.display=""):e._o.ctrlArea&&(e._o.ctrlArea.style.display="none");
}),o.allowPause?v.addClass(r,o.pauseCss||o.playingCss):v.addClass(r,o.playingCss),
o.playdotDom&&(e.surportSeekRange()?(o.playdotDom.style.display="block",this._g.canDragBar=!0):(o.playdotDom.style.display="none",
this._g.canDragBar=!1));
}
o.loadingDom&&(o.loadingDom.style.display=4==t?"block":"none");
},a.prototype._updateProgress=function(e){
this._g.barDraging||this._updateProgressBar(e);
},a.prototype._updateProgressBar=function(e){
var t=this._o,a=this.player,o=a.getDuration();
if(o){
var r=this._countProgress(o,e);
t.progress&&(t.progress.style.width=r),t.playtimeDom&&e>=0&&(t.playtimeDom.innerHTML=u(e)),
t.playdotDom&&(t.playdotDom.style.left=r);
}
},a.prototype._countProgress=function(e,t){
return Math.min(t/e*100,100)+"%";
},a.prototype.destory=function(){
this.player&&this.player.destory();
},a.prototype.setOption=function(e){
e.duration&&(this._g.seekData.duration=e.duration),this._extend(e);
},a.prototype.setMusicPlayerOption=function(e){
e.duration&&this._g&&this._g.seekData&&(this._g.seekData.duration=e.duration),this.player&&this.player.setOption(e);
},a.prototype.getBackgroundAudioState=function(e){
return this.player.getBackgroundAudioState(e);
},a.prototype.report11899=function(e){
var t=this._o,a=2===t.type?3:4===t.type?6:0,o=window.withoutIframe?window:window.parent.window;
"[object Object]"!==Object.prototype.toString.call(e)&&(e={}),S.report(11899,_extends({},{
Type:a,
BizUin:window.biz||"",
Mid:window.parseInt(window.mid,10)||0,
Idx:window.parseInt(window.idx,10)||0,
VoiceId:t.songId||"",
scene:1*o.scene
},e));
},{
init:d,
renderPlayer:r,
formatTime:u,
decodeStr:_,
encodeStr:g
};
});define("pages/qqmusic_tpl.html.js",[],function(){
return'<span id="qqmusic_main_<#=musicid#>_<#=posIndex#>" class="js_wap_qqmusic db pages_reset music_area <#if(!musicSupport){#> unsupport<#}#>">\n    <span class="tc tips_global unsupport_tips" <#if(show_not_support!==true){#>style="display:none;"<#}#>>\n    当前浏览器不支持播放音乐或语音，请在微信或其他浏览器中播放    </span>\n    <span class="db music_card appmsg_card_context appmsg_card_active">\n            <a id="qqmusic_home_<#=musicid#>_<#=posIndex#>" class="music_card_bd">\n                <span class="music_card_title"><#=music_name#></span>\n                <span class="music_card_desc"><#=singer#></span>\n                <span class="music_card_source <#if(musictype==2){#>music_card_source_kugou<#}#>">\n                  <img src="<#=musicIcon#>" alt=""></span>\n            </a>\n            <span id="qqmusic_play_<#=musicid#>_<#=posIndex#>" class="music_card_ft">\n                <i class="weui-play-btn"></i>\n                <!--\n                <img src="<#=window.icon_qqmusic_default#>" alt="" class="pic_qqmusic_default">\n                -->\n                <img src="<#=albumurl#>" data-autourl="<#=audiourl#>" data-musicid="<#=musicid#>" class="music_card_thumb" alt="">\n            </span>\n    </span>\n</span>\n';
});define("new_video/ctl.js",["common/comm_report.js","biz_wap/utils/ajax.js"],function(e){
"use strict";
var i,r=window.withoutIframe?window:window.parent.window,t=e("common/comm_report.js");
if(parent==window)i=window;else try{
{
r.location.href;
}
i=r;
}catch(n){
i=window;
}
var a=i.user_uin,o=Math.floor(i.user_uin/100)%20;
a||(o=-1);
var d=function(){
return o>=0;
};
i.__webviewid||(i.__webviewid=+new Date+"_"+Math.ceil(1e3*Math.random()));
var s=function(){
var e=i.mid,r=i.idx,t="";
t=e&&r?e+"_"+r:"";
var n=i.__webviewid,o=[a,t,n].join("_");
return o;
},c=function(i){
if(20>o)try{
var t=i.vid||"",n={};
n.__biz=r.biz||"",n.vid=t,n.clienttime=+new Date;
var a=r.mid,c=r.idx,p="";
p=a&&c?a+"_"+c:t,n.type="undefined"!=typeof i.type?i.type:a&&c?1:2,n.id=p,n.hit_bizuin=i.hit_bizuin||"",
n.hit_vid=i.hit_vid||"",n.webviewid=s(),n.step=i.step||0,n.orderid=i.orderid||0,
n.ad_source=i.ad_source||0,n.traceid=i.traceid||0,n.ext1=i.ext1||"",n.ext2=i.ext2||"",
n.r=Math.random(),n.devicetype=r.devicetype,n.version=r.clientversion,n.is_gray=d()?1:0,
n.mid=a||"",n.idx=c||"",n.url=r.location.href,n.screen_num=i.screen_num||0,n.screen_height=i.screen_height||0,
n.ori_status=i.ori_status||3,n.fromid=i.fromid||0,n.sessionid=window.sessionid||"",
n.appmsg_scene=window.source||(i.cgiData?i.cgiData.scene:0)||0,!n.appmsg_scene&&n.fromid?n.appmsg_scene=n.fromid:!n.fromid&&n.appmsg_scene&&(n.fromid=n.appmsg_scene),
n.total_range=i.total_range||0,n.current_range=i.current_range||0,n.duration=i.duration||0;
var m=e("biz_wap/utils/ajax.js");
m({
url:"/mp/ad_video_report?action=user_action",
type:"post",
data:n
});
}catch(_){}
},p=function(e){
try{
var i=e.vid||"",n={};
n.BizUin=r.biz||"",n.Vid=i,n.ClientTime=+new Date;
var a=r.mid,o=r.idx,c="";
c=a&&o?a+"_"+o:i,n.Type="undefined"!=typeof e.type?e.type:a&&o?1:2,n.Id=c,n.HitBizUin=parseInt(e.hit_bizuin)||0,
n.HitVid=e.hit_vid||"",n.WebViewId=s(),n.Step=parseInt(e.step,10)||0,n.OrderId=(e.orderid||"").toString(),
n.AdSource=parseInt(e.ad_source,10)||0,n.TraceId=(e.traceid||"").toString(),n.Ext1=(e.ext1||"").toString(),
n.Ext2=(e.ext2||"").toString(),n.r=Math.random(),n.DeviceType=r.devicetype,n.ClientVersion=parseInt(r.clientversion),
n.IsGray=d()?1:0,n.msgid=parseInt(a,10)||0,n.itemidx=parseInt(o,10)||0,n.Url=r.location.href,
n.ScreenNum=parseInt(e.screen_num,10)||0,n.ScreenHeight=parseInt(e.screen_height,10)||0,
n.OrStatus=parseInt(e.ori_status,10)||3,n.Fromid=parseInt(e.fromid,10)||0,n.SessionId=(window.sessionid||"").toString(),
n.AppmsgScene=parseInt(window.source||(e.cgiData?e.cgiData.scene:0),10)||0,!n.AppmsgScene&&n.Fromid?n.AppmsgScene=n.Fromid:!n.Fromid&&n.AppmsgScene&&(n.Fromid=n.AppmsgScene),
n.AppmsgScene=parseInt(n.AppmsgScene,10)||0,n.Fromid=parseInt(n.Fromid,10)||0,n.TotalRange=parseInt(e.total_range,10)||0,
n.CurrentRange=parseInt(e.current_range,10)||0,n.Duration=parseInt(e.duration,10)||0,
n.RemindTrafficSize=parseInt(e.remind_traffic_size,10)||0,n.TrafficReminderType=parseInt(e.traffic_reminder_type,10)||0,
t.report(12710,n);
}catch(p){}
};
return{
report:c,
getWebviewid:s,
showAd:d,
commReport:p
};
});define("appmsg/without_iframe/video_appmsg.js",["biz_common/utils/string/html.js","biz_common/tmpl.js","appmsg/without_iframe/video_appmsg.html.js","biz_common/utils/url/parse.js","appmsg/without_iframe/iframe_communicate.js","appmsg/without_iframe/video_plugin/video_tail.js","biz_wap/utils/ajax.js","biz_common/dom/event.js","pages/qq_video_info.js","pages/video_plugin/pause_tips.js","pages/video_plugin/video_app.js","pages/video_ctrl.js","biz_wap/jsapi/core.js"],function(i){
"use strict";
i("biz_common/utils/string/html.js");
var e=i("biz_common/tmpl.js"),t=i("appmsg/without_iframe/video_appmsg.html.js"),o=i("biz_common/utils/url/parse.js"),n=i("appmsg/without_iframe/iframe_communicate.js"),d=i("appmsg/without_iframe/video_plugin/video_tail.js"),s=i("biz_wap/utils/ajax.js"),a=i("biz_common/dom/event.js"),_=i("pages/qq_video_info.js"),r=i("pages/video_plugin/pause_tips.js"),m=i("pages/video_plugin/video_app.js"),p=i("pages/video_ctrl.js"),v=i("biz_wap/jsapi/core.js");
return function(){
function i(i,e){
var t=e||window.location.search,o=new RegExp("(^|&)"+i+"=([^&]*)(&|$)"),n=t.substr(t.indexOf("?")+1).match(o);
return null!=n?n[2]:"";
}
function c(i){
return document.querySelector("#js_mp_video_container_"+f.vid+" #"+i);
}
function u(){
f.ori_status=1*y.ori_status===1?1:1*y.ori_status===2?2:3,f.showComment=1*y.show_comment===1,
f.comment_id=y.comment_id,f.vid=y.vid,f.ckey=y.ckey,f.ckey_ad=y.ckey_ad,f.__biz=y.__biz,
f.uin=y.uin,f.mid=y.mid,f.idx=y.idx,f.scene=y.scene||i("scene",window.location.href)||0,
f.autoplay=!!f.container.getAttribute("__sec_open_auto_play__"),f.dom={
js_mpvedio:c("js_mpvedio_wrapper_"+f.vid),
page_content:c("page-content")
};
}
function w(){
var i=f.ratio;
y.vw&&y.vh&&(i=y.vw/y.vh);
var e=y.vw||f.dom.js_mpvedio.offsetWidth,t=Math.ceil(e/i),o=[],s=!1;
p.showPauseTips()&&!y.is_mp_video&&(o.push(new r),s=!0),s&&!y.is_mp_video&&o.push(new m),
o.push(new d({
vid:y.vid,
nickname:y.bizNickname,
headImg:y.roundHeadImg,
userName:y.username,
isAppMsg:!0,
cgiData:y,
reportData:{
BizUserName:y.__biz,
MsgId:1*y.mid,
Idx:1*y.idx,
EnterId:y.enterid,
VideoId:y.vid,
Scene:y.scene,
Subscene:1*y.subscene,
OrStatus:1*y.ori_status,
HitBizuin:1*y.hit_bizuin,
HitVid:y.hit_vid,
SessionIdStr:window.sessionid,
Url:window.location.href,
Device:window.devicetype
}
})),f.myPlayer=new _.mpVideoPlayer({
preview:!(1*y.preview!==1),
isInIframe:!0,
hit_bizuin:y.hit_bizuin,
hit_vid:y.hit_vid,
fromid:f.scene,
ori_status:f.ori_status,
is_mp_video:y.txvideo_vid?0:y.is_mp_video,
plugins:o,
oriVid:f.vid,
vid:y.txvideo_vid?y.txvideo_vid:f.vid,
ckey:y.txvideo_vid?"":f.ckey,
ckey_ad:f.ckey_ad,
width:e,
height:t,
container:"#js_mpvedio_wrapper_"+f.vid,
__biz:f.__biz,
uin:f.uin,
mid:f.mid,
idx:f.idx,
comment_id:f.comment_id,
scene_type:0,
autoplay:f.autoplay,
videoMd5:y.video_md5,
headImgUrl:window.round_head_img,
canShareVideo:!y.is_in_pay_subscribe,
leaveReport12710Type:1,
onReady:function(){
if(f.dom.js_mpvedio.style.height="100%",(p.showVideoDetail()||p.showReprint())&&!f.hasShowBotbar){
var i=c("bottom_bar");
i&&(i.style.display="",f.hasShowBotbar=!0,n.postMessage({
type:"addVideoIframeHeight",
data:{
vid:y.txvideo_vid||f.id,
height:f.mpVideoBotH
}
}));
}
n.postMessage({
type:"videoInited",
data:{
vid:f.id,
ori_status:f.ori_status,
hit_bizuin:y.hit_bizuin,
hit_vid:y.hit_vid
}
});
}
},y);
}
function h(){
w();
}
function l(){
var e=c("h5_profile_btn");
e&&2===y.ori_status&&a.tap(e,function(){
var i="https://mp.weixin.qq.com/mp/profile_ext?action=home&__biz="+y.source_encode_biz+"&scene=111#wechat_redirect";
-1!==navigator.userAgent.indexOf("WindowsWechat")||-1!==navigator.userAgent.indexOf("Mac OS")?location.href=i:v.invoke("openUrlWithExtraWebview",{
url:i,
openType:1
},function(e){
-1===e.err_msg.indexOf("ok")&&(location.href=i);
});
});
var t=c("video_detail_btn");
t&&1===y.media_source&&a.tap(t,function(){
var e=["https://mp.weixin.qq.com/mp/video?t=pages/video_detail_new","&vid=",f.vid,"&mid=",f.mid,"&__biz=",f.__biz,"&idx=",f.idx,"&sn=",window.sn||i("sign",window.location.href)||"","&vidsn=",y&&y.vidsn?y.vidsn:"","&scene=100#wechat_redirect"];
f.myPlayer&&f.myPlayer.extendMpReportData({
detail_click:1
}),window.location.href=e.join("");
});
}
function b(i,e){
s({
url:e,
type:"GET",
f:"json",
success:function(e){
var t=JSON.parse(e),o=i.vid,n=i.vh,d=i.vw,s=i.ratio;
y={
hit_bizuin:t.hit_bizuin,
hit_vid:t.hit_vid,
txvideo_vid:t.txvideo_vid,
txvideo_openid:t.txvideo_openid,
ckey:t.ckey,
ckey_ad:t.ckey_ad,
video_title:t.video_title,
ori_status:t.ori_status,
nick_name:window.nickname,
hit_username:t.hit_username,
is_mp_video:t.is_mp_video,
vh:n,
vw:d,
scene:window.scene||0,
ratio:s,
openid:t.openid,
show_comment:window.show_comment,
comment_id:window.comment_id,
vid:o,
__biz:window.biz,
mid:window.mid,
idx:window.idx,
uin:window.uin,
media_source:t.media_source,
vidsn:t.vidsn,
username:t.biz_user_name,
preview:window.preview,
source_encode_biz:window.source_encode_biz,
video_md5:t.video_md5,
is_in_pay_subscribe:1*window.isPaySubscribe||0,
bizNickname:window.nickname,
roundHeadImg:window.round_head_img,
enterid:1*window.enterid,
subscene:window.subscene
},u(),h(),l();
}
});
}
function g(i,n){
for(var d=i.getAttribute("data-src")||i.getAttribute("src"),s=o.getQuery("vid",d),a=i.getAttribute("data-vw"),_=i.getAttribute("data-vh"),r=i.getAttribute("data-ratio"),m=document.createElement("span"),p=i.attributes,v=p.length-1;v>=0;v--)m.setAttribute(p[v].name,p[v].value);
m.id="js_mp_video_container_"+s,m.setAttribute("vid",s),m.style.cssText=i.style.cssText,
m.style.display="none";
var c=e.tmpl(t,{
vid:s,
video_h:_
},!1);
m.innerHTML=c;
var u=i.parentNode;
return u?(u.lastChild===i?u.appendChild(m):u.insertBefore(m,i.nextSibling),u.removeChild(i),
f.container=m,b({
iframe:m,
vid:s,
vh:_,
vw:a,
ratio:r
},n),m):null;
}
var f={
hasShowBotbar:!1,
mpVideoBotH:37,
showComment:!0,
loverCount:{}
},y={};
return{
createMpVideoDom:g
};
};
});define("biz_wap/jsapi/leaveReport.js",["biz_wap/utils/ajax.js","biz_wap/jsapi/core.js","biz_common/utils/url/parse.js","biz_wap/utils/log.js"],function(e){
"use strict";
function t(e){
var t={};
return"undefined"!=typeof uin&&(t.uin=uin),"undefined"!=typeof key&&(t.key=key),
"undefined"!=typeof pass_ticket&&(t.pass_ticket=pass_ticket),"undefined"!=typeof wxtoken&&(t.wxtoken=wxtoken),
"undefined"!=typeof window.devicetype&&(t.devicetype=window.devicetype),"undefined"!=typeof window.clientversion&&(t.clientversion=window.clientversion),
"undefined"!=typeof appmsg_token?t.appmsg_token=appmsg_token:e.indexOf("advertisement_report")>-1&&((new Image).src=location.protocol+"//mp.weixin.qq.com/mp/jsmonitor?idkey=68064_13_1&r="+Math.random()),
t.x5=l?"1":"0",t.f="json",f.join(e,t);
}
function o(e){
return e&&"object"==typeof e;
}
function n(e,t){
if(o(e)&&o(t))for(var n in t)Object.prototype.hasOwnProperty.call(t,n)&&(e[n]=t[n]);
}
function r(e){
u("[leaveReport 1]"),console.log("[leaveReport 1]");
var r={};
for(var i in y){
r[i]||(r[i]={});
for(var a=0;a<y[i].length;a++){
var p=y[i][a];
"function"==typeof p?n(r[i],p(e)):o(p)&&n(r[i],p);
}
}
u("[leaveReport getDataFunc.length "+_.length+"]"),console.log("[leaveReport getDataFunc.length "+_.length+"]");
for(var a=0;a<_.length;a++){
var s=_[a](e);
o(s)&&g.push(s);
}
for(var a=0;a<g.length;a++)g[a].reportUrl&&(g[a].reportUrl=t(g[a].reportUrl));
return r.data={
requestList:g
},r;
}
function i(e){
"function"==typeof e?_.push(e):o(e)&&g.push(e);
}
function a(e,t){
y[e]||(y[e]=[]),y[e].push(t);
}
function p(e){
var t=r(!0);
c.invoke("handleMPPageAction",{
action:"reportByLeaveForMPGateway",
reportData:t
},function(o){
if(o&&o.err_msg&&-1!==o.err_msg.indexOf(":ok"))_=[],g=[],y={},"function"==typeof e&&e(o);else{
_=[],g=[];
var n=t.data.requestList.length;
t.data.requestList.forEach(function(t){
t.reportUrl&&s({
type:t.method||"GET",
url:t.reportUrl,
data:t.reportData,
async:!1,
success:function(t){
--n<0&&"function"==typeof e&&e({
err_msg:"handleMPPageAction:ok",
fallback:!0,
resp:t
});
},
error:function(t,o){
--n<0&&"function"==typeof e&&e({
err_msg:"handleMPPageAction:fail",
fallback:!0,
err:o
});
}
});
});
}
});
}
var s=e("biz_wap/utils/ajax.js"),c=e("biz_wap/jsapi/core.js"),f=e("biz_common/utils/url/parse.js"),u=e("biz_wap/utils/log.js"),l=-1!=navigator.userAgent.indexOf("TBS/"),d={},v=!1;
try{
d=top.window.document;
}catch(w){
v=!0;
}
if(!v&&top.window.__leaveReport)return top.window.__leaveReport;
if(window.__leaveReport)return window.__leaveReport;
var _=[],g=[],y={};
c.on("reportOnLeaveForMP",function(){
return r(!1);
});
var h={
reportNow:p,
addReport:i,
addSpecificReport:a
};
return window.__leaveReport=h,h;
});define("biz_wap/utils/hand_up_state.js",["biz_common/dom/event.js"],function(n){
"use strict";
function e(){
if("hidden"in document)return"hidden";
for(var n=["webkit","moz","ms","o"],e=0;e<n.length;e++)return n[e]+"Hidden"in document,
n[e]+"Hidden";
return null;
}
function i(){
var n=e();
return n?document[n]:!1;
}
function t(){
return r;
}
var d=n("biz_common/dom/event.js"),o=e(),r=0,u=0;
if(o){
var m=o.replace(/[H|h]idden/,"")+"visibilitychange";
d.on(document,m,function(){
i()?u=(new Date).getTime():r+=(new Date).getTime()-u;
},!1);
}
return{
getHandUpTime:t,
isHidden:i
};
});define("biz_common/utils/http.js",[],function(){
"use strict";
function t(){
var t=document.getElementsByTagName("html");
if(t&&1==!!t.length){
t=t[0].innerHTML;
var e=t.replace(/[\x00-\xff]/g,""),n=t.replace(/[^\x00-\xff]/g,"");
return 1*n.length+3*e.length+"<!DOCTYPE html><html></html>".length;
}
return 0;
}
return{
htmlSize:t()
};
});define("biz_common/utils/cookie.js",[],function(){
"use strict";
var e={
get:function(e){
if(""==e)return"";
var t=new RegExp(e+"=([^;]*)"),n=document.cookie.match(t);
return n&&n[1]||"";
},
set:function(e,t,n){
var o=new Date;
return o.setDate(o.getDate()+(n||1)),n=o.toGMTString(),document.cookie=e+"="+t+";expires="+n,
!0;
}
};
return e;
});define("appmsg/open_url_with_webview.js",["biz_wap/jsapi/core.js"],function(e){
"use strict";
var r=e("biz_wap/jsapi/core.js"),n=-1!=navigator.userAgent.indexOf("WindowsWechat"),i=function(e,i){
if(n)return location.href=e,!1;
i=i||{};
var o=i.sample||0;
o*=1e3;
var t=window.user_uin||0,s=0!==t&&Math.floor(t/100)%1e3<o;
return s?void r.invoke("openUrlWithExtraWebview",{
url:e,
openType:i.openType||1,
scene:i.scene||"",
bizUsername:i.user_name||""
},function(e){
e&&"openUrlWithExtraWebview:ok"===e.err_msg?i.resolve&&i.resolve():i.reject&&i.reject();
}):void(i.reject&&i.reject());
};
return i;
});var _extends=Object.assign||function(e){
for(var n=1;n<arguments.length;n++){
var i=arguments[n];
for(var t in i)Object.prototype.hasOwnProperty.call(i,t)&&(e[t]=i[t]);
}
return e;
};
define("appmsg/album_keep_read.js",["page/appmsg_new/mod/album_read.css","biz_common/dom/event.js","biz_common/dom/class.js","pages/mod/bottom_modal.js","biz_wap/utils/openUrl.js","pages/utils.js","biz_wap/utils/ajax.js","common/comm_report.js","common/utils.js","biz_common/dom/offset.js","biz_wap/utils/wapsdk.js"],function(e){
"use strict";
function n(e,n){
v.jsmonitor({
id:223326,
key:e,
value:n
});
}
function i(){
var e=arguments.length<=0||void 0===arguments[0]?{}:arguments[0];
b.report(21277,_extends({},x,e));
}
function t(){
function e(){
if(!t){
var e=w.getOffset(h).offsetTop,o=f.getScrollTop();
o+f.getInnerHeight()>=e+a&&e+a>=o&&(i({
ActionType:1
}),n(11),t=!0);
}
}
var t=void 0,a=h.offsetHeight/2;
f.bindDebounceScrollEvent(e),e();
}
function a(){
var e=window.appmsg_album_info;
if(e.link){
var n=e.link.replace("#wechat_redirect","&subscene=159&subscene="+window.source+"&scenenote="+encodeURIComponent(window.location.href)+"&nolastread=1#wechat_redirect");
_.openUrlWithExtraWebview(n.htmlDecode());
}
}
function o(e){
e&&c.on(e,"click","."+y.itemClassName,function(e){
var n=e.delegatedTarget;
if(!u.hasClass(n,"album_read_directory_current")){
var t=void 0;
t=n.dataset.url.includes("#")?n.dataset.url.replace("#",T+"&scene=190#"):n.dataset.url+(T+"&scene=190"),
i({
ActionType:5,
Url:t
}),p.jumpUrl(t,!0),u.addClass(n,"album_read_directory_disabled");
}
});
}
function s(){
var e=document.createElement("div"),n=document.createElement("span");
return n.innerHTML="#"+window.appmsg_album_info.title,e.appendChild(n),e.innerHTML;
}
function r(e){
g({
type:"GET",
url:"/mp/appmsgalbum?action=paging&__biz="+window.biz+"&album_id="+y.albumId+"&cur_msgid="+y.msgid+"&cur_itemidx="+y.idx+"&count="+y.pageCount,
timeout:5e3,
dataType:"json",
success:function(n){
n.base_resp&&0===n.base_resp.ret&&e(n.getalbum_resp);
},
error:function(){
console.log("[error]");
}
});
}
function l(){
function e(e){
var n=arguments.length<=1||void 0===arguments[1]?!1:arguments[1],i=arguments.length<=2||void 0===arguments[2]?!0:arguments[2],t=document.createDocumentFragment();
if(_)if(n){
h=1;
for(var a=0;a<e.length;a++)if(e[a].msgid.toString()===y.msgid.toString()&&e[a].itemidx.toString()===y.idx.toString()){
h=a;
break;
}
e.forEach(function(e,n){
e.index=p?c-(n-h):c+(n-h);
});
}else e.forEach(i?function(e,n){
e.index=p?v.index-n-1:v.index+n+1;
}:function(n,i){
n.index=p?w.index+(e.length-i):w.index-(e.length-i);
});
return e.forEach(function(e){
var n=document.createElement("div");
if(u.addClass(n,y.itemClassName),e.msgid.toString()===window.mid.toString()&&e.itemidx.toString()===window.idx.toString()?u.addClass(n,"album_read_directory_current"):1===e.user_read_status&&u.addClass(n,"album_read_directory_disabled"),
n.innerText=_?e.index+"."+e.title:e.title,n.setAttribute("data-url",e.url),e.is_paid){
var i="已付费";
n.innerHTML+='<span class="wx_icon_pay_tag wx_icon_pay_tag_paid">'+i+"</span>";
}else if(e.is_pay_subscribe){
var a="付费";
n.innerHTML+='<span class="wx_icon_pay_tag">'+a+"</span>";
}
t.appendChild(n);
}),t;
}
function t(e){
1*e.reverse_continue_flag||(b=!1),1*e.continue_flag||(f=!1);
}
var l=document.createElement("div");
l.style.position="relative";
var d=[],c=void 0,_=void 0,p=void 0,b=!0,f=!0,w=void 0,v=void 0,h=1,x={
extClass:"album_read_directory",
hasBtn:!0,
btnSlot:'<div id="js_topic_detail" class="weui-btn__word-wrp">\n                  <span class="weui-btn__word">详情</span>\n                  <i class="weui_right_arrow"></i>\n                </div>',
title:s(),
btnClickCb:function(){
i({
ActionType:6
}),n(15),a();
},
cb:function(){
r(function(n){
j.hideLoading(),p=n.base_info.is_reverse,c=n.base_info.cur_article_num,_=c?1:0,l.appendChild(e(n.article_list,!0)),
w=n.article_list[0],v=n.article_list[n.article_list.length-1],t(n),f||j.showEndLine();
var i=l.childNodes[h];
setTimeout(function(){
i.offsetTop+i.clientHeight>j.contentAreaWrp.clientHeight&&j.scrollTo(0,l.offsetHeight);
},200);
});
},
onShow:function(){
i({
ActionType:4
}),n(14);
},
onPullUpLoad:function(){
f&&(j.showPullUpLoading(),g({
type:"GET",
url:"/mp/appmsgalbum?action=paging&__biz="+window.biz+"&album_id="+y.albumId+"&begin_msgid="+v.msgid+"&begin_itemidx="+v.itemidx+"&count="+y.pageCount,
timeout:5e3,
dataType:"json",
success:function(n){
j.hidePullUpLoading();
var i=n.base_resp&&1*n.base_resp.ret;
if(0===i){
var a=n.getalbum_resp.article_list;
t(n.getalbum_resp),l.appendChild(e(a,!1,!0)),d=d.concat(a),j.finishPullUpLoad(),
v=d[d.length-1],1*n.getalbum_resp.continue_flag||j.showEndLine();
}
},
error:function(){}
}));
},
onPullDownLoad:function(){
b&&(j.showPullDownLoading(),g({
type:"GET",
url:"/mp/appmsgalbum?action=paging&__biz="+window.biz+"&album_id="+y.albumId+"&begin_msgid="+w.msgid+"&begin_itemidx="+w.itemidx+"&count="+y.pageCount+"&isbackward=1",
timeout:5e3,
dataType:"json",
success:function(n){
j.hidePullDownLoading();
var i=n.base_resp&&1*n.base_resp.ret;
if(0===i){
var a=n.getalbum_resp.article_list,o=n.getalbum_resp.continue_flag;
n.getalbum_resp.continue_flag=n.getalbum_resp.reverse_continue_flag,n.getalbum_resp.reverse_continue_flag=o,
t(n.getalbum_resp);
var s=e(a,!1,!1),r=l.firstChild;
l.insertBefore(s,r),d=a.concat(d),j.scrollTo(0,r.offsetTop-69),j.finishPullDownLoad(),
w=d[0];
}
},
error:function(){}
}));
}
};
window.appmsg_album_info.size<=4&&(x.top=screen.height/2-(screen.height-window.innerHeight)+"px"),
j=new m(l,x),j.showLoading(),j.show(),o(l);
}
function d(){
var e=arguments.length<=0||void 0===arguments[0]?{}:arguments[0],t=document.getElementById("js_album_directory");
c.on(t,"click",function(){
j?j.show():l();
});
var a=document.getElementById("js_album_prev"),o=document.getElementById("js_album_next");
e.pre_article_link?c.on(a,"click",function(){
var t=void 0;
i({
ActionType:2,
SubActionType:1
}),n(12),t=e.pre_article_link.includes("#")?e.pre_article_link.replace("#",T+"&scene=189#"):e.pre_article_link+(T+"&scene=189"),
location.href=t.replace(/&amp;/g,"&");
}):a.parentNode.removeChild(a),e.next_article_link?c.on(o,"click",function(){
var t=void 0;
i({
ActionType:2,
SubActionType:2
}),n(13),t=e.next_article_link.includes("#")?e.next_article_link.replace("#",T+"&scene=189#"):e.next_article_link+(T+"&scene=189"),
location.href=t.replace(/&amp;/g,"&");
}):o.parentNode.removeChild(o);
}
e("page/appmsg_new/mod/album_read.css");
var c=e("biz_common/dom/event.js"),u=e("biz_common/dom/class.js"),m=e("pages/mod/bottom_modal.js"),_=e("biz_wap/utils/openUrl.js"),p=e("pages/utils.js"),g=e("biz_wap/utils/ajax.js"),b=e("common/comm_report.js"),f=e("common/utils.js"),w=e("biz_common/dom/offset.js"),v=e("biz_wap/utils/wapsdk.js"),h=document.getElementById("js_album_keep_read"),y={
link:window.appmsg_album_info.link,
albumId:window.appmsg_album_info.id,
msgid:window.mid,
idx:window.idx,
pageCount:10,
itemClassName:"album_read_directory_item"
},x={
MsgId:1*y.msgid,
ItemIdx:1*y.idx,
BizUin:window.biz,
Itemshowtype:1*window.item_show_type,
SessionId:window.sessionid,
EnterId:1*window.enterid,
Scene:1*window.source,
SubScene:1*window.subscene,
Albumid:y.albumId,
Albumtype:window.appmsg_album_info.type,
Title:window.appmsg_album_info.title
},j=void 0,T="&cur_album_id="+y.albumId;
return{
init:function(e){
h&&(e.pre_article_link||e.next_article_link)&&(document.getElementById("js_album_keep_read_title").innerHTML=window.appmsg_album_info.title,
document.getElementById("js_album_keep_read_size").innerHTML=window.appmsg_album_info.size,
document.getElementById("js_album_keep_read_pre_title").innerHTML=e.pre_article_title||"",
document.getElementById("js_album_keep_read_next_title").innerHTML=e.next_article_title||"",
h.style.display="block",d(e),t());
}
};
});define("appmsg/more_read.js",["biz_common/utils/string/html.js","biz_common/tmpl.js","biz_wap/utils/ajax.js","appmsg/more_read_tpl.html.js","biz_wap/utils/openUrl.js","biz_common/dom/event.js","biz_wap/utils/jsmonitor_report.js","common/utils.js"],function(n){
"use strict";
function i(n){
for(var i=r.getInnerHeight(),e=document.documentElement.clientWidth||window.innerWidth,t=document.body.scrollHeight||document.body.offsetHeight,s=document.body.scrollTop||document.documentElement.scrollTop,m=[],a=0;a<l.length;a++){
var w=[l[a].bizuin||window.biz||"",l[a].mid||"",l[a].idx||""].join("_");
m.push(w);
}
m=m.join("#");
var p=c[n.index].getBoundingClientRect(),h="fans_read_cnt="+l[n.index].fans_read_cnt,g={
act:n.action||0,
bizuin:window.biz||"",
msgid:window.mid||"",
idx:window.idx||"",
scene:window.source||"",
sub_scene:window.subscene||"",
get_a8_key_scene:window.ascene||"",
screen_height:i,
screen_width:e,
screen_num:Math.ceil(t/i),
action_screen_num:Math.ceil((p.top+p.height+s)/i),
start_time_ms:_,
action_time_ms:Date.now(),
more_msg:m,
a_bizuin:l[n.index].bizuin||window.biz||"",
a_msgid:l[n.index].mid||"",
a_idx:l[n.index].idx||"",
rank:n.index+1,
tip:h,
session_id:u
};
o({
url:"/mp/appmsgreport?action=more_read",
type:"POST",
data:g,
timeout:2e3,
async:!1,
mayAbort:!0
});
var b=1===n.action?4:5;
d.setSum(110809,b,1);
}
function e(){
if(l){
for(var n=0,t=r.getInnerHeight(),o=0;o<c.length;o++)if(c[o].dataset.show)n++;else{
var s=c[o].getBoundingClientRect();
s.top+s.height<t&&(c[o].dataset.show=1,i({
action:1,
index:o
}));
}
n>=c.length&&a.off(window,"scroll",e);
}
}
n("biz_common/utils/string/html.js");
var t=n("biz_common/tmpl.js"),o=n("biz_wap/utils/ajax.js"),s=n("appmsg/more_read_tpl.html.js"),m=n("biz_wap/utils/openUrl.js"),a=n("biz_common/dom/event.js"),d=n("biz_wap/utils/jsmonitor_report.js"),r=n("common/utils.js"),l=null,c=null,_=Date.now(),u=""+_+"_"+Math.random().toString(36).substring(2);
return a.on(window,"scroll",e),function(n,e){
l=e,n.innerHTML=t.tmpl(s,{
list:l
},!1),c=n.getElementsByClassName("more_read_link");
for(var o=0;o<c.length;o++)a.on(c[o],"click",function(n){
return function(){
window.__second_open__?m.openUrlWithExtraWebview(l[n].link.htmlDecode()):window.location.href=l[n].link.htmlDecode(),
i({
action:2,
index:n
});
};
}(o));
n.style.display="";
};
});var _extends=Object.assign||function(e){
for(var t=1;t<arguments.length;t++){
var n=arguments[t];
for(var o in n)Object.prototype.hasOwnProperty.call(n,o)&&(e[o]=n[o]);
}
return e;
};
define("appmsg/comment.js",["biz_wap/ui/weui.js","biz_common/utils/string/html.js","biz_common/utils/wxgspeedsdk.js","appmsg/comment_report.js","biz_wap/utils/device.js","biz_common/utils/url/parse.js","biz_wap/jsapi/core.js","common/utils.js","biz_common/dom/event.js","biz_wap/utils/ajax.js","biz_common/tmpl.js","biz_wap/utils/fakehash.js","appmsg/log.js","appmsg/comment/comment_tpl.html.js","appmsg/comment/comment_write.html.js","appmsg/comment/comment_write_old.html.js","pages/utils.js","biz_wap/utils/mmversion.js","common/comm_report.js","appmsg/set_font_size.js","biz_wap/utils/jsmonitor_report.js","common/keyboard.js","appmsg/comment/comment_write_dialog/comment_write_dialog.js","appmsg/comment/comment_list/comment_list.js","appmsg/comment/comment_dialog/comment_dialog.js","appmsg/comment/comment_input/comment_input.js","appmsg/comment/comment_length.js","common/fixed_input.js","appmsg/emotion/emotion_panel.js","pages/scrollY.js","appmsg/comment/comment_report.js","appmsg/rec_report_key.js","pages_new/common_share/video/store.js"],function(e){
"use strict";
e("biz_wap/ui/weui.js"),e("biz_common/utils/string/html.js");
var t=e("biz_common/utils/wxgspeedsdk.js"),n=e("appmsg/comment_report.js"),o=e("biz_wap/utils/device.js"),i=e("biz_common/utils/url/parse.js"),s=e("biz_wap/jsapi/core.js"),m=e("common/utils.js"),a=e("biz_common/dom/event.js"),c=e("biz_wap/utils/ajax.js"),r=e("biz_common/tmpl.js"),l=e("biz_wap/utils/fakehash.js"),d=e("appmsg/log.js"),p=e("appmsg/comment/comment_tpl.html.js"),u=e("appmsg/comment/comment_write.html.js"),_=e("appmsg/comment/comment_write_old.html.js"),g=e("pages/utils.js"),w=e("biz_wap/utils/mmversion.js"),y=e("common/comm_report.js"),f=e("appmsg/set_font_size.js"),I=e("biz_wap/utils/jsmonitor_report.js"),h=e("common/keyboard.js"),b=e("appmsg/comment/comment_write_dialog/comment_write_dialog.js"),v=e("appmsg/comment/comment_list/comment_list.js"),C=e("appmsg/comment/comment_dialog/comment_dialog.js"),j=e("appmsg/comment/comment_input/comment_input.js"),k=e("appmsg/comment/comment_length.js"),L=e("common/fixed_input.js"),D=e("appmsg/emotion/emotion_panel.js"),T=e("pages/scrollY.js"),S=e("appmsg/comment/comment_report.js"),x=S.report22214,R=e("appmsg/rec_report_key.js"),A=R.RecActionType,F=R.reportRecAction,P=!window.isPaySubscribe||window.isPaySubscribe&&window.isPaid,E=k.getLimit("comment"),z=0;
try{
z=1*window.atob(window.biz);
}catch(W){}
var B={
BizUin:z,
BizUinStr:window.biz||"",
AppMsgId:window.parseInt(window.mid,10)||0,
ItemIdx:window.parseInt(window.idx,10)||0,
ItemShowType:window.parseInt(window.item_show_type,10)||0,
SessionIdStr:window.sessionid||"",
EnterId:window.parseInt(window.enterid,10)||0,
Scene:window.parseInt(window.source,10)||0,
SubScene:window.parseInt(window.subscene,10)||0
},H={
bizuin:z,
msgid:window.parseInt(window.mid,10)||0,
itemidx:window.parseInt(window.idx,10)||0,
scene:window.parseInt(window.source,10)||0
},M=!1,O=void 0,N=void 0,q=void 0,U=void 0,K=!1,V=[],Y={},G=0,J=Date.now(),Q=[],X=null,Z=!1,$=!1,et=!1,tt=!1,nt=!1,ot=null,it=!1,st=null,mt=null,at={
commentCount:"",
scrollCount:0,
nickName:"我",
headImg:"",
offset:0,
commentId:window.comment_id,
onlyFansCanComment:0,
onlyFansDaysCanComment:0,
isFans:0,
isFansDays:0,
replyFlag:0,
reportData:{
scene:0,
idkey:"",
moreList:27,
repeatList:25,
errList:18,
handleList:26,
addCommentErr:19,
errComment:18,
repeatContent:24,
repeatContentID:23
},
contentIDs:[],
canC2CReply:!1,
cmtFixedInput:null,
cmtDialog:null,
cmtList:null,
myList:null,
articleContent:null
},ct=100,rt=location.href,lt=w.is_wxwork,dt=o.os.pc&&!lt,pt="comment_editing",ut="my_comment_empty_data",_t="weui-btn_disabled",gt="discuss_form_write_show",wt="icon_discuss_keyboard",yt=navigator.userAgent.indexOf("MicroMessenger")>-1,ft=g.getId("js_cmt_area"),It=rt.indexOf("vconsole=1")>0||document.cookie&&document.cookie.indexOf("vconsole_open=1")>-1,ht={
vertical:0,
horizontal:0
};
0===window.orientation||180===window.orientation?(ht.vertical=m.getInnerHeight(),
ht.horizontal=screen.width-(screen.height-ht.vertical)):(ht.horizontal=m.getInnerHeight(),
ht.vertical=screen.width-(screen.height-ht.horizontal+60));
var bt=g.getId("activity-name")||"";
bt&&(bt=g.trim(bt.innerText)||""),window.pageCommentReportData&&window.pageCommentReportData.idkey&&(It&&console.log("init reportData"),
at.reportData=window.pageCommentReportData),"undefined"!=typeof window.comment_id?at.commentId=window.comment_id:window.cgiData&&"undefined"!=typeof window.cgiData.comment_id&&(at.commentId=window.cgiData.comment_id),
yt||(ft&&(ft.style.display="none"),at.commentId=0),It&&console.info("[图文评论] 评论ID:",at.commentId);
var vt=function(){
return w.isWechat?w.isInMiniProgram?0:h.canUseKeyboard?2:(w.isIOS||w.isAndroid)&&(w.gtVersion("7.0.8")||m.isNativePage())?2:0:0;
}(),Ct=function(e,t){
e&&(e.style.display=t||"block");
},jt=function(e){
e&&(e.style.display="none");
},kt=function(e){
if(!e)return!1;
var t=m.getScrollTop(),n=e.offsetTop;
return t+m.getInnerHeight()>n&&n>=t;
},Lt=function(e,n){
Math.random()<.999||(t.saveSpeeds({
uin:window.uin,
pid:"https:"===window.location.protocol?18:9,
speeds:[{
sid:29,
time:e
},{
sid:30,
time:n
}]
}),t.send());
},Dt=function(e){
var t=arguments.length<=1||void 0===arguments[1]?"":arguments[1];
if("undefined"!=typeof e)if(at.reportData.idkey)I.setSum(at.reportData.idkey,e,1);else{
var n=new Image,o=Math.random();
n.src="/mp/jsreport?key="+e+"&content="+t+"&r="+o;
}
},Tt=function(){
Array.prototype.forEach.call(g.getByClass("js_more_reply"),function(e){
var t=e.dataset.myId;
-1===Q.indexOf(t)&&kt(e)&&(y.report(19462,_extends({
PersonalCommentId:parseInt(t,10)||0,
CommentId:parseInt(at.commentId,10)||0,
actiontype:1,
wording:"余下N条",
number:parseInt(e.dataset.num,10)||0,
devicetype:dt?1:2
},H)),Q.push(t));
});
},St=function(){
if(!(2>G)){
var e=m.getInnerHeight();
[at.myList.getItemList(),at.cmtList.getItemList()].forEach(function(t,n){
var o=at[n?"cmtList":"myList"];
t.some(function(t){
if(!t.isExposed){
var i=t.getBoundingClientRect(),s=.5*i.height;
if(i.bottom>s&&i.top<e-s){
t.isExposed=!0;
var m=t.dataset,a={
PersonalCommentId:1*m.myId,
ReplyId:0,
IsPopup:0,
IsReplyOther:0,
CommentReplyType:n?1:2
};
if(m.replyId){
var c=o.getData({
type:"reply",
contentId:m.contentId,
replyId:1*m.replyId
});
a.ReplyId=c.reply_id,a.IsReplyOther=c.to_nick_name&&c.to_content?1:0;
}
x(a);
}else if(i.top>=e-s)return!0;
}
return!1;
});
});
}
},xt=function(){
N||(N=!0,new n({
comment_id:at.commentId,
appmsgid:window.appmsgid,
idx:window.idx,
item_show_type:window.item_show_type||0,
biz:window.biz
}),Tt());
},Rt=function sn(){
try{
kt(Y.loading)&&K&&(I.setLogs({
id:28307,
key:45,
value:1,
lc:1,
log0:""
}),a.off(window,"scroll",sn));
}catch(e){
console.error(e);
}
},At=function(){
var e=function(e,t,n){
at.onlyFansDaysCanComment&&0===at.isFansDays?((t||e).innerHTML="作者已设置关注7天后才可留言",
Ct(e),t&&Ct(t)):at.onlyFansCanComment&&0===at.isFans?((t||e).innerHTML="作者已设置关注后才可以留言",
Ct(e),t&&Ct(t)):P&&(dt?(Ct(Y.commentPC),Ct(Y.inputPC)):(t&&(jt(t),Ct(e)),Ct(n)));
};
return function(){
if(!lt){
var t=g.qs(".js_cmt_nofans_mine",ft),n=g.qs(".js_cmt_nofans_elected",ft),o=g.qs(".js_cmt_nofans_single",ft),i=g.qs(".js_cmt_nofans_single_inner",o),s=g.qs(".js_cmt_addbtn",o);
at.myList.count?(jt(n),jt(n.nextElementSibling),jt(o),jt(i),jt(s),e(t,null,t.nextElementSibling)):at.cmtList.count?(jt(t),
jt(t.nextElementSibling),jt(o),jt(i),jt(s),e(n,null,n.nextElementSibling)):(jt(t),
jt(t.nextElementSibling),jt(n),jt(n.nextElementSibling),e(o,i,s));
}
};
}(),Ft=function(){
at.myList.showAll(),St(),Y.mylistFolder&&(Y.mylistFolder.parentNode.removeChild(Y.mylistFolder),
Y.mylistFolder=null);
},Pt=function(){
var e=!0,t=!0,n=!1,o=null,i=null,s=null,m=function(e){
e&&window.scrollTo(0,e.getBoundingClientRect().top+g.getScrollTop()-6);
};
return function(a,c){
if(At(),e&&window.goContentId&&!c&&a)if(!window.onload_endtime||new Date-window.onload_endtime<1e3){
if($&&(null===o&&(o=null!==at.myList.getData({
contentId:window.goContentId
})),o))return void("none"!==ft.style.display&&(Ft(),m(""!==window.goReplyId?at.myList.getReply(window.goContentId,1*window.goReplyId):at.myList.getComment(window.goContentId)),
e=!1));
Z&&(null===i&&(s=at.cmtList.getData({
contentId:window.goContentId
}),i=null!==s),i&&(t&&""!==window.goReplyId&&(s.reply_new.reply_total_cnt&&s.reply_new.reply_total_cnt!==s.reply_new.reply_list.length?at.cmtDialog.showDialog(at.cmtList.getData({
contentId:window.goContentId
}),1*window.goReplyId):n=!0,t=!1),$&&(m(n?at.cmtList.getReply(window.goContentId,1*window.goReplyId):at.cmtList.getComment(window.goContentId)),
e=!1)));
}else e=!1;
};
}(),Et=function(e){
var n=Date.now(),o=e.resp,i=e.loadTime,s=e.forceRefresh,m=e.notFirstRender;
if(at.onlyFansCanComment=o.only_fans_can_comment,at.isFans=o.is_fans,window.isPaySubscribe&&!window.isPaid&&(at.canC2CReply=!1),
at.replyFlag=at.canC2CReply?o.reply_flag:0,Dt(at.reportData.handleList,encodeURIComponent(JSON.stringify({
comment_id:at.commentId,
offset:at.offset,
url:rt
}))),1!==o.enabled?(ft&&(ft.style.display="none"),o.elected_comment=[],o.elected_comment_total_cnt=0):ft&&(ft.style.display="block"),
0===at.offset){
at.headImg=o.logo_url,at.nickName=o.nick_name,s&&(at.contentIDs=[]);
var a=o.elected_comment;
a&&a.length?(Ct(Y.main),at.cmtList.render(a),o.elected_comment_total_cnt<=10&&Ct(Y.statement),
q||"5"!==window.item_show_type||(q=!0,Math.random()<.1&&(t.saveSpeeds({
uin:window.uin,
pid:675,
speeds:[{
sid:27,
time:Date.now()-window.logs.pagetime.page_begin
}]
}),t.send()))):jt(Y.main),Z=!0,Pt(s,m);
var c=ft.getBoundingClientRect().y;
location.href.indexOf("scrolltodown")>-1&&c&&window.scrollTo(0,c-25);
}else{
var a=o.elected_comment;
a&&a.length&&at.cmtList.add({
data:a
});
}
0===o.elected_comment_total_cnt?(at.offset=-1,jt(Y.loading),jt(Y.statement)):at.offset+ct>=o.elected_comment_total_cnt?(at.offset=-1,
jt(Y.loading),Ct(Y.statement)):at.offset+=o.elected_comment.length,window.ipados13_font_scale&&f.setFontSize(Y.main,window.ipados13_font_scale/100),
xt(),g.setTwoTabHeight("js_comment_content"),i&&Lt(i,Date.now()-n);
},zt=function(e){
if(at.commentId=window.comment_id,0!==Number(at.commentId)){
var t=e.notFirstRender,n=e.forceRefresh,o=e.cb;
n=n===!0,n&&(at.offset=0);
var s=m.getScrollTop(),r=document.documentElement.scrollHeight;
if(!(K||-1===at.offset||at.offset>0&&r-s-m.getInnerHeight()>500)){
if("number"==typeof at.commentCount&&0===at.commentCount&&!n)return void Et({
resp:{
enabled:1,
elected_comment:[],
elected_comment_total_cnt:0,
my_comment:[],
only_fans_can_comment:at.onlyFansCanComment,
is_fans:at.isFans,
logo_url:at.headImg,
nick_name:at.nickName
}
});
var l=i.join("/mp/appmsg_comment",{
action:"getcomment",
scene:at.reportData.scene,
appmsgid:window.appmsgid,
idx:window.idx,
comment_id:at.commentId,
offset:at.offset,
limit:ct,
send_time:window.send_time
},!0),p=+new Date;
K=!0,Ct(Y.loading),Rt();
try{
at.scrollCount++,n&&(V=[]),at.scrollCount>1&&!n&&Dt(at.reportData.moreList,encodeURIComponent(l)),
V.indexOf(l)>-1&&Dt(at.reportData.repeatList,encodeURIComponent(l)),V.push(l);
}catch(u){
console.error(u);
}
It&&console.info("[图文评论] 开始请求评论数据:",l),d("[Appmsg comment] start get comment data, url:"+l),
c({
url:l,
dataType:"json",
success:function(e){
var i=e.base_resp&&e.base_resp.ret;
0===i?o&&o({
resp:e,
forceRefresh:n,
notFirstRender:t,
loadTime:Date.now()-p
}):Dt(at.reportData.errList,"type:resperr;url:"+encodeURIComponent(l)+";ret="+i),
d("[Appmsg comment] get comment success");
},
error:function(){
Dt(at.reportData.errList,"type:ajaxerr;url:"+encodeURIComponent(l)),d("[Appmsg comment] get comment ajax error");
},
complete:function(){
K=!1,jt(Y.loading),a.off(window,"scroll",Rt);
}
});
}
}
},Wt=function(e){
var t=v.validContent(e);
return t.valid&&dt&&(t.content=X.value),t;
},Bt=!1,Ht=function(e){
var t=e.content,n=e.successBegin,o=e.successEnd,s=e.fail,m=e.complete;
Bt||!function(){
Bt=!0,O!==t&&(J=Date.now());
var e=i.join("/mp/appmsg_comment",{
action:"addcomment",
scene:at.reportData.scene,
appmsgid:window.appmsgid,
idx:window.idx,
comment_id:at.commentId,
sn:window.sn
},!0);
c({
url:e,
data:{
content:t,
title:bt,
head_img:at.headImg,
nickname:at.nickName,
client_id:J
},
type:"POST",
dataType:"json",
success:function(i){
switch("function"==typeof n&&n(),+i.ret){
case 0:
var m={
content:t,
nick_name:at.nickName,
create_time:Date.now()/1e3|0,
is_elected:0,
logo_url:at.headImg,
like_status:0,
like_num_format:0,
like_num:0,
is_from_friend:0,
is_from_me:1,
my_id:i.my_id,
content_id:i.content_id,
reply_new:{
reply_list:[]
},
needAnimation:!0
};
return Ct(Y.mylistContainer),Ct(Y.mylistFooter),at.myList.add({
data:[m],
mode:"unshift"
}),void("function"==typeof o&&o());

case-6:
window.weui.alert("你留言的太频繁了，休息一下吧");
break;

case-7:
window.weui.alert("你还未关注该公众号，不能参与留言");
break;

case-10:
window.weui.alert("字数不能多于"+E+"个");
break;

case-15:
window.weui.alert("留言已关闭");
break;

case-18:
window.weui.alert("你在此文章的留言次数已达上限");
break;

default:
O=t,window.weui.alert("系统错误，请重试");
}
Dt(at.reportData.addCommentErr,"type:resperr;url:"+encodeURIComponent(e)+";ret="+i.ret),
"function"==typeof s&&s();
},
error:function(t){
console.log(t),Dt(at.reportData.addCommentErr,"type:ajaxerr;url:"+encodeURIComponent(e)),
"function"==typeof s&&s();
},
complete:function(){
Bt=!1,"function"==typeof m&&m();
}
});
}();
},Mt=function(){
var e=X.getSubmit(),t=X.getInput();
if(e.disabled!==!0){
var n=Wt(dt?X.value:t.value),o=n.valid,i=n.content;
o&&(e.disabled=!0,Ht({
content:i,
successBegin:function(){
!dt&&X.hideEmotionPannel();
},
successEnd:function(){
dt?(X.hide(),Ct(Y.inputPC)):t.value="";
},
complete:function(){
""!==t.value&&(e.disabled=!1);
}
}));
}
},Ot=function(){
var e=i.join("/mp/appmsg_comment",{
action:"getmycomment",
scene:at.reportData.scene,
appmsgid:window.appmsgid,
idx:window.idx,
comment_id:at.commentId
},!0);
0===G&&(G=1,Array.prototype.forEach.call(Y.myCmtLoading,Ct),c({
url:e,
dataType:"json",
success:function(t){
var n=t.base_resp&&t.base_resp.ret;
if(0===n){
G=2;
var o=t.my_comment;
o&&o.length&&(Ct(Y.mylistContainer),Ct(Y.mylistFooter),at.myList.render(o),at.myList.getIsOversize()&&Ct(Y.mylistFolder));
}else G=0,Dt(at.reportData.errComment,"type:resperr;url:"+encodeURIComponent(e)+";ret="+n);
$=!0,Pt(!0,!1);
},
error:function(){
G=0,Dt(at.reportData.errComment,"type:ajaxerr;url:"+encodeURIComponent(e));
},
complete:function(){
Array.prototype.forEach.call(Y.myCmtLoading,jt);
}
}));
},Nt=function(){
return{
enterEditing:function(){
et=!0,h.canUseCancel;
},
leaveEditing:function(){
et&&(et=!1,h.canUseCancel&&w.isAndroid&&document.body.style.removeProperty("margin-bottom"));
}
};
}(),qt=Nt.leaveEditing,Ut=function(){
switch(vt){
case 2:
at.cmtWriteDialog.show();
break;

case 1:
s.invoke("handleMPPageAction",{
action:"writeComment",
title:bt,
comment_id:at.commentId,
style:"white"
});
}
return vt;
},Kt=function(e){
M=!0,U=m.getScrollTop(),!dt&&jt(Y.article),at.myList.changeContainer(Y.mylistOld),
Ft(),Ct(Y.mine),document.body.classList[at.myList.count?"remove":"add"](ut),window.__second_open__&&o.os.ios&&Ct(Y.fakebar),
window.scrollTo(0,0),Ot(),!e&&setTimeout(function(){
return X.focus();
},3);
},Vt=function(){
M=!1,at.myList.changeContainer(Y.mylist),jt(Y.mine),Ct(Y.article),window.scrollTo(0,U),
X.blur(),document.body.classList.remove(pt),document.body.classList.remove(ut);
},Yt=function(t,n){
if(1*window.item_show_type===5){
var i=e("pages_new/common_share/video/store.js");
i.dispatch("mp-video-player/auto-next-plugin/cancelAutoNextWhenTipsShowed",6);
}
switch(t&&t.preventDefault(),Ut()){
case 2:
y.report(19048,_extends({
EventType:1,
IsFans:at.isFans,
CommentPageType:3
},B));
break;

case 1:
y.report(19048,_extends({
EventType:1,
IsFans:at.isFans,
CommentPageType:2
},B));
break;

case 0:
default:
if(m.isNativePage()||document.body.classList.add(pt),n)return It&&console.log("FakeHash on comment"),
void Kt();
t.preventDefault(),window.__second_open__&&o.os.ios?Kt():(It&&console.log("push comment"),
l.push("comment")),y.report(19048,_extends({
EventType:1,
IsFans:at.isFans,
CommentPageType:1
},B));
}
},Gt=w.isAndroid?30:0,Jt=function(e,t){
if(tt){
var n=Y.commentWriteArea.getBoundingClientRect(),o=n.bottom,i=ht[0===window.orientation||180===window.orientation?"vertical":"horizontal"],s=o-(i-e)-(t?0:Gt),a=Math.abs(s),c=g.getScrollTop(),r=document.body.scrollHeight-c-i;
s>r?document.body.style.marginBottom=(document.body.style.marginBottom?parseInt(document.body.style.marginBottom,10):0)+s-r+"px":0>s&&a>c&&(at.articleContent.style.marginTop=(at.articleContent.style.marginTop?parseInt(at.articleContent.style.marginTop,10):0)+a-c+"px");
var l={
distance:s,
end:w.isAndroid?function(){
var n=Y.commentWriteArea.getBoundingClientRect().bottom,o=m.getInnerHeight()-(t?e:0);
n!==o&&T.start({
distance:n-o,
duration:.1
});
}:null
};
150>a?l.speed=300:l.duration=.3,T.start(l);
}
},Qt=function(e){
e=e||k.getLength(Y.input.value),Y.cmtTips.innerHTML=e>=E-k.remindWordCount&&E>e?"还可以输入"+(E-e)+"个字":e===E?"达到"+E+"字输入上限":e>E?"已超出"+(e-E)+"字":"";
},Xt=function(){
var e=k.getLength(Y.input.value);
Y.cmtSubmitBtn.classList[e&&E>=e?"remove":"add"](_t),Qt();
},Zt=function(){
Y.cmtEmotionBtn.classList.remove(wt),Y.cmtEmotionBtn.setAttribute("aria-pressed",!1),
h.lastData.keyboard&&!nt&&Jt(h.lastData.keyboard);
},$t=function(e){
Y.input.blur(),tt=!1,document.body.style.removeProperty("margin-bottom"),at.articleContent.style.removeProperty("margin-top"),
at.cmtEmotionPanel.hide(),Y.commentWriteArea.style.height=0,Y.commentWriteArea.classList.remove(gt),
mt&&(clearTimeout(mt),mt=null),e===!0?jt(Y.commentWriteMask):mt=setTimeout(function(){
jt(Y.commentWriteMask),mt=null;
},500),w.isIOS&&s.invoke("handleMPPageAction",{
action:"opInputAccessoryView",
show:!0
});
},en=function(){
var e=Y.cmtSubmitBtn.classList;
if(!e.contains(_t)){
var t=Wt(Y.input.value),n=t.valid,o=t.content;
n&&(at.cmtWriteDialog.disableSubmit(),e.add(_t),Ht({
content:o,
successEnd:function(){
at.cmtFixedInput.setInput(""),setTimeout(function(){
nt=!1,$t();
},10);
},
fail:function(){
e.remove(_t);
}
}));
}
},tn=function(){
a.on(Y.mylistFolder,"click",Ft),a.on(window,"scroll",Rt),a.on(window,"scroll",Tt),
a.bindVisibilityChangeEvt(function(e){
e&&!kt(Y.cmtContainer)&&zt({
notFirstRender:!0,
forceRefresh:!0,
cb:Et
}),w.isIOS&&"hidden"===document.visibilityState&&$t(!0);
});
var e=function t(){
Y.mylistFolder?kt(Y.mylistFolder)&&(y.report(19462,_extends({
CommentId:parseInt(at.commentId,10)||0,
actiontype:1,
wording:"展开全部留言",
number:at.myList.count,
devicetype:1
},H)),a.off(window,"scroll",t)):a.off(window,"scroll",t);
};
a.on(window,"scroll",e),e(),m.bindDebounceScrollEvent(St),dt?a.tap(Y.inputPC,function(){
jt(Y.inputPC),X.show(Y.inputPC);
}):!function(){
h.onGetKeyboardHeight(function(e){
var t=e.keyboard;
st&&(clearTimeout(st),st=null),!nt&&Jt(t);
}),a.on(ft,"click",function(e){
var t=e.target;
if(t.classList.contains("js_cmt_addbtn")){
var n=window.getComputedStyle(Y.commentWriteAreaInner),o=n.marginTop,i=n.marginBottom;
tt=!0,nt=!1,Y.commentWriteArea.style.height=Y.commentWriteAreaInner.offsetHeight+parseInt(o,10)+parseInt(i,10)+"px",
Y.commentWriteArea.classList.add(gt),Ct(Y.commentWriteMask),it||(st=setTimeout(function(){
it=!0;
},1e3)),w.isIOS?(s.invoke("handleMPPageAction",{
action:"opInputAccessoryView",
show:!1
}),Y.input.focus()):setTimeout(function(){
return Y.input.focus();
});
}
});
var e=null;
switch(a.on(Y.input,"touchstart",function(t){
nt=!1,w.isAndroid?setTimeout(function(){
return Y.input.focus();
}):Y.input.focus(),e=1===t.touches.length?t.touches[0]:null;
}),a.on(Y.input,"paste",function(e){
var t=e.clipboardData.getData("text"),n=k.getLength(t),o=k.getLength(Y.input.value);
if(o+n>E){
e.preventDefault();
for(var i=E-o,s="",m=0,a=t.length;a>m&&i>0&&(i-=/[^\x00-\xff]/.test(t[m])?1:.5,!(0>i));m++)s+=t[m];
var c=Y.input,r=c.value.substring(0,c.selectionStart),l=c.value.substring(c.selectionEnd),d=c.selectionStart+s.length;
c.value=r+s+l,at.cmtFixedInput.setPlaceholder(c.value),Xt(),c.scrollTop=c.scrollHeight,
c.setSelectionRange(d,d);
}
}),a.on(Y.input,"keydown",function(e){
if(!e.altKey&&!e.ctrlKey)switch(e.keyCode){
case 8:
case 9:
case 12:
case 16:
case 17:
case 18:
case 20:
case 27:
case 33:
case 34:
case 35:
case 36:
case 37:
case 38:
case 39:
case 40:
case 45:
case 46:
case 144:
case 175:
case 174:
case 179:
case 173:
case 172:
case 180:
case 170:
break;

default:
k.getLength(Y.input.value)>=E&&e.preventDefault();
}
}),a.on(Y.cmtCancel,"click",$t),a.on(Y.commentWriteMask,"touchstart",$t),a.on(Y.cmtWriteTitle,"touchstart",function(e){
return e.preventDefault();
}),Y.commentWriteAreaInner.addEventListener("touchmove",function(t){
if(t.target===Y.input)if(null===e)t.preventDefault();else{
var n=t.changedTouches[0].clientY-e.clientY;
(Y.input.scrollTop<=0&&n>0||Y.input.scrollTop>=Y.input.scrollHeight-Y.input.offsetHeight&&0>n)&&t.preventDefault();
}else t.preventDefault();
},{
passive:!1
}),w.isAndroid?a.on(window,"resize",function(){
if(tt){
var e=0===window.orientation||180===window.orientation?"vertical":"horizontal",t=ht[e],n=m.getInnerHeight();
t>n?Zt():(!nt&&$t(),n>t&&(ht[e]=n));
}
}):a.on(Y.input,"blur",function(){
ot=setTimeout(function(){
!it&&$t(),ot=null;
});
}),a.on(Y.cmtEmotionBtn,"click",function(){
ot&&(clearTimeout(ot),ot=null),at.cmtEmotionPanel.isShow?(nt=!1,w.isAndroid?setTimeout(function(){
return Y.input.focus();
}):Y.input.focus()):(Y.cmtEmotionBtn.classList.add(wt),Y.cmtEmotionBtn.setAttribute("aria-pressed",!0),
nt=!0,Y.input.blur()),at.cmtEmotionPanel.toggle();
}),a.on(Y.cmtSubmitBtn,"click",function(){
ot&&(clearTimeout(ot),ot=null),en();
}),a.on(Y.keyboardTool,"touchstart",function(e){
var t=e.target;
t===Y.cmtEmotionBtn||t===Y.cmtSubmitBtn&&!t.classList.contains(_t)||e.preventDefault();
}),vt){
case 2:
break;

case 1:
m.listenMpPageAction(function(e){
"deleteComment"===e.action&&at.cmtList.remove({
myId:e.personal_comment_id
}),"deleteCommentReply"===e.action&&at.cmtList.remove({
type:"reply",
myId:e.personal_comment_id,
replyId:e.replyId
}),"praiseComment"===e.action&&(e.reply_id&&0!==e.reply_id?(at.cmtList.setLikeInfo({
type:"reply",
myId:e.personal_comment_id,
replyId:e.reply_id,
likeStatus:e.is_like
}),at.cmtDialog.setReplyLikeInfo({
myId:e.personal_comment_id,
replyId:e.reply_id,
likeStatus:e.is_like
})):at.cmtList.setLikeInfo({
myId:e.personal_comment_id,
likeStatus:e.is_like
}));
});
break;

case 0:
Y.goback&&a.on(Y.goback,"click",function(e){
e.preventDefault(),Vt(),jt(Y.fakebar);
}),o.os.ios&&window.__second_open__&&!function(){
var e=null,t=null;
a.on(window,"orientationchange",function(){
"none"!==Y.fakebar.style.display&&(clearTimeout(e),e=setTimeout(function(){
window.innerWidth!==parseFloat(getComputedStyle(Y.fakebar).width)&&(clearTimeout(t),
Y.mine.style.height=m.getInnerHeight()+"px",window.scrollBy&&window.scrollBy(0,1),
t=setTimeout(function(){
window.scrollBy&&window.scrollBy(0,-1),Y.mine.style.height="";
},100));
},50));
});
}();
}
}();
},nn=function(e){
if(at.canC2CReply=0!==(256&e.test_flag),at.onlyFansCanComment=e.only_fans_can_comment,
at.nickName=e.nick_name,at.isFans=e.is_fans,at.headImg=e.logo_url,at.commentCount=e.comment_count,
at.onlyFansDaysCanComment=e.only_fans_days_can_comment,at.isFansDays=e.is_fans_days,
at.articleContent=e.articleContent||g.getId("img-content"),window._has_comment=!0,
console.log("inwechat",yt,"commentid",at.commentId),!yt||0===Number(at.commentId))return void(window._has_comment=!1);
var t=g.getId("js_cmt_container");
ft&&(t.insertAdjacentHTML("afterbegin",r.tmpl(u,{
deviceIsPc:dt
})),at.cmtWriteDialog=new b({
globalData:at,
canC2CReply:at.canC2CReply,
onSubmit:function(e){
var t=Wt(e),n=t.valid,o=t.content;
n&&(at.cmtWriteDialog.disableSubmit(),Ht({
content:o,
successEnd:function(){
at.cmtWriteDialog.hide(),at.cmtWriteDialog.setInputValue(""),F(A.kComment);
},
fail:function(){
at.cmtWriteDialog.enableSubmit();
}
}));
}
}),ft.innerHTML=r.tmpl(p,{
isWxWork:lt
})),dt?document.body.classList.add("pages_skin_pc"):0===vt&&document.body.insertAdjacentHTML("beforeend",r.tmpl(_,{
textPageTitle:1*window.item_show_type===10?g.getId("js_text_content").innerHTML.replace(/<(\/?)(?=((a(\s|>))|(\/a))).*?>/g,""):window.msg_title.html(1)
},!1)),Y={
article:g.getId("js_article"),
mine:g.getId("js_cmt_mine"),
main:g.getId("js_cmt_main"),
goback:g.getId("js_cmt_goback"),
list:g.getId("js_cmt_list"),
mylistContainer:g.getId("js_my_list_container"),
mylist:g.getId("js_my_list"),
mylistFolder:g.getId("js_my_list_folder"),
mylistFooter:g.getId("js_my_list_footer"),
mylistOld:g.getId("js_my_list_old"),
morelist:g.getId("js_cmt_morelist"),
loading:g.getId("js_cmt_loading"),
fakebar:g.getId("js_fake_bar"),
statement:g.getId("js_cmt_statement"),
myCmtLoading:g.qsAll(".js_mycmt_loading"),
cmtContainer:t,
commentPC:g.getId("js_comment_pc"),
inputPC:g.getId("js_cmt_input_pc"),
containerPC:g.getId("js_cmt_container_pc"),
addbtnPC:g.getId("js_cmt_addbtn_pc"),
emotionSwitchPC:g.getId("js_emotion_wrp_pc"),
inputHolder:g.getId("js_cmt_input_holder"),
commentWriteArea:g.getId("js_cmt_write_area"),
updateDialog:g.getId("js_update_dialog"),
updateCancel:g.getId("js_update_cancel"),
updateConfirm:g.getId("js_update_confirm"),
deleteReplyPanel:g.getId("js_delete_reply_panel"),
deleteReplyConfirm:g.getId("js_delete_reply_confirm"),
deleteReplyCancel:g.getId("js_delete_reply_cancel"),
cmtDialog:g.getId("js_cmt_dialog")
},Y.commentWriteArea&&(Y.commentWriteMask=Y.commentWriteArea.nextElementSibling,
Y.commentWriteAreaInner=g.qs(".js_cmt_write_area_inner",Y.commentWriteArea),Y.cmtWriteTitle=g.qs(".js_title",Y.commentWriteAreaInner),
Y.cmtCancel=g.qs(".js_cancel",Y.commentWriteAreaInner),Y.input=g.qs(".js_cmt_input",Y.commentWriteAreaInner),
Y.keyboardTool=g.qs(".js_keyboard_tool",Y.commentWriteAreaInner),Y.cmtEmotionBtn=g.qs(".js_emotion_btn",Y.keyboardTool),
Y.cmtSubmitBtn=g.qs(".js_cmt_submit_btn",Y.keyboardTool),Y.cmtTips=g.qs(".js_cmt_tips",Y.keyboardTool)),
dt||(at.cmtFixedInput=new L({
input:Y.input,
onFocus:function(){
w.isIOS&&Zt();
},
onInput:Xt
}),at.cmtEmotionPanel=new D({
input:Y.input,
limit:E,
counter:function(e){
return k.getLength(e);
},
onChange:function(e){
var t=e.type,n=e.value;
return"action"===t&&"done"===n?void en():(Xt(),at.cmtFixedInput.setPlaceholder(Y.input.value),
void(nt=!0));
},
onShow:function(e){
tt?Jt(e,!0):at.cmtEmotionPanel.hide();
},
onTouchmove:function(e){
e.stopPropagation();
}
})),at.cmtDialog=new C({
globalData:at,
canAddComment:P,
onGetReplyList:function(e,t){
t.filter(function(e){
return 2===e.is_from;
}).forEach(function(t){
at.cmtList.setLikeInfo({
type:"reply",
contentId:e,
replyId:t.reply_id,
likeStatus:t.reply_like_status,
likeNum:t.reply_like_num
});
});
}
}),at.cmtList=new v({
globalData:at,
container:Y.list,
type:"elected",
canAddComment:P,
onPraise:function(e,t,n,o,i){
!at.canC2CReply&&at.myList.setLikeInfo({
type:e,
contentId:t,
replyId:n,
likeStatus:o,
likeNum:i
}),at.cmtDialog.setReplyLikeInfo({
contentId:t,
replyId:n,
likeStatus:o,
likeNum:i
});
},
onRender:function(){
St();
},
onAdd:function(e,t,n,o,i){
!at.canC2CReply&&at.myList.add({
data:e,
mode:t,
type:n,
contentId:o,
pos:i
}),St();
},
onRemove:function(e,t,n){
!at.canC2CReply&&at.myList.remove({
type:e,
contentId:t,
replyId:n.reply_id
}),St();
},
onEmpty:function(e){
"comment"===e&&(jt(Y.main),jt(Y.statement),At());
},
beforeShowKeyboard:function(){
qt();
}
}),at.myList=new v({
globalData:at,
container:Y.mylist,
type:"mine",
canAddComment:P,
onPraise:function(e,t,n,o,i){
!at.canC2CReply&&at.cmtList.setLikeInfo({
type:e,
contentId:t,
replyId:n,
likeStatus:o,
likeNum:i
});
},
onRender:function(){
St();
},
onAdd:function(e,t,n,o,i){
!at.canC2CReply&&"reply"===n&&at.cmtList.add({
data:e,
mode:t,
type:n,
contentId:o,
pos:i
}),St(),Ft(),At();
},
onRemove:function(e,t,n){
Y.mylistFolder&&at.myList.showTopItems()&&Ft(),!at.canC2CReply&&at.cmtList.remove({
type:e,
contentId:t,
replyId:n.reply_id
}),St();
},
onEmpty:function(){
jt(Y.mylistContainer),jt(Y.mylistFooter),M&&document.body.classList.add(ut),At();
},
beforeShowKeyboard:function(){
qt();
}
}),window.cl=at.cmtList,window.ml=at.myList,0===vt&&window.__second_open__&&o.os.ios&&(Y.mine.style.marginBottom=getComputedStyle(Y.fakebar).height),
!e.notAutoGetComment&&zt({
forceRefresh:!0,
cb:Et
}),"1"===i.getQuery("js_my_comment")&&(1===vt?Ut():0!==vt||dt||Kt(!0)),Ot(),tn(),
dt?X=new j({
placeholder:"留言被公众号精选后，将对所有人可见",
submitText:"留言",
length:E,
onSubmit:Mt,
onHide:function(){
Ct(Y.inputPC);
}
}):0===vt&&(X=new j({
placeholder:"留言被公众号精选后，将对所有人可见",
submitText:"留言",
length:E,
onSubmit:Mt,
onClick:function(){
window.__second_open__&&jt(Y.fakebar);
},
onBlur:function(){
"none"!==Y.mine.style.display&&Ct(Y.fakebar);
}
}),X.show(g.getId("js_comment_input_old"),{
renderType:"append"
}));
},on=function(){
dt||0!==vt||(l.on("comment",function(){
Yt(null,!0);
}),l.on("article",function(){
It&&console.log("FakeHash on article"),Vt();
}),l.on(function(e){
"comment"===e&&Vt();
}));
};
return on(),{
initComment:nn,
getCommentData:zt,
renderComment:Et
};
});