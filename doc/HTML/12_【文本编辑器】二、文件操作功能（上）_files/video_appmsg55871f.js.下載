define("pages/video_appmsg.js",["biz_common/utils/string/html.js","common/init_share_btn.js","pages/iframe_communicate.js","pages/video_plugin/video_tail.js","biz_common/dom/event.js","pages/qq_video_info.js","pages/video_plugin/pause_tips.js","pages/video_plugin/video_app.js","pages/video_plugin/video_like.js","pages/video_ctrl.js","biz_wap/jsapi/core.js"],function(i){
"use strict";
i("biz_common/utils/string/html.js"),i("common/init_share_btn.js");
var e=i("pages/iframe_communicate.js"),a=i("pages/video_plugin/video_tail.js"),o=i("biz_common/dom/event.js"),t=i("pages/qq_video_info.js"),n=i("pages/video_plugin/pause_tips.js"),d=i("pages/video_plugin/video_app.js"),s=i("pages/video_plugin/video_like.js"),w=i("pages/video_ctrl.js"),c=i("biz_wap/jsapi/core.js"),_={
hasShowBotbar:!1,
mpVideoBotH:37,
showComment:!0,
loverCount:{}
};
!function(){
function i(){
top!=window&&-1!=location.href.indexOf("__td=qq.com")&&(document.domain="qq.com");
var i=window.cgiData;
_.ori_status=1*i.ori_status===1?1:1*i.ori_status===2?2:3,_.showComment=1*i.show_comment===1?!0:!1,
_.comment_id=i.comment_id,_.id=i.id,_.ckey=i.ckey,_.ckey_ad=i.ckey_ad,_.__biz=i.__biz,
_.uin=i.uin,_.mid=i.mid,_.idx=i.idx,_.scene=window.cgiData.scene||g("scene",window.parent.window.location.href)||0,
_.autoplay=!!window.__auto_play__,_.dom={
js_mpvedio:v("js_mpvedio"),
page_content:v("page-content")
};
}
function p(){
m();
}
function r(){
var i=v("h5_profile_btn");
i&&2==window.cgiData.ori_status&&o.tap(i,function(){
var i="https://mp.weixin.qq.com/mp/profile_ext?action=home&__biz="+window.cgiData.source_encode_biz+"&scene=111#wechat_redirect";
-1!=navigator.userAgent.indexOf("WindowsWechat")||-1!=navigator.userAgent.indexOf("Mac OS")?window.parent.location.href=i:c.invoke("openUrlWithExtraWebview",{
url:i,
openType:1
},function(e){
-1==e.err_msg.indexOf("ok")&&(window.parent.location.href=i);
});
});
var e=v("video_detail_btn");
e&&1==window.cgiData.media_source&&o.tap(e,function(){
var i=["https://mp.weixin.qq.com/mp/video?t=pages/video_detail_new","&vid=",_.id,"&mid=",_.mid,"&__biz=",_.__biz,"&idx=",_.idx,"&sn=",window.parent.window.sn||g("sign",window.parent.window.location.href)||"","&vidsn=",window.cgiData&&window.cgiData.vidsn?window.cgiData.vidsn:"","&scene=100#wechat_redirect"];
_.myPlayer&&_.myPlayer.extendMpReportData({
detail_click:1
}),window.parent.window.location.href=i.join("");
});
}
function g(i){
var e=arguments[1]||window.location.search,a=new RegExp("(^|&)"+i+"=([^&]*)(&|$)"),o=e.substr(e.indexOf("?")+1).match(a);
return null!=o?o[2]:"";
}
function m(){
var i=w.getRatio();
cgiData.vw&&cgiData.vh&&(i=cgiData.vw/cgiData.vh);
var o=cgiData.vw||_.dom.js_mpvedio.offsetWidth,c=Math.ceil(o/i),p=[],r=!1;
w.showVideoLike()&&!window.cgiData.is_mp_video&&(p.push(new s),r=!0),w.showPauseTips()&&!window.cgiData.is_mp_video&&(p.push(new n),
r=!0),r&&!window.cgiData.is_mp_video&&p.push(new d),p.push(new a({
nickname:window.cgiData.bizNickname,
headImg:window.cgiData.roundHeadImg,
userName:window.cgiData.username,
isAppMsg:!0,
reportData:{
BizUserName:window.cgiData.__biz,
MsgId:1*window.cgiData.mid,
Idx:1*window.cgiData.idx,
EnterId:window.cgiData.enterid,
VideoId:window.cgiData.id,
Scene:window.cgiData.scene,
Subscene:1*window.cgiData.subscene,
OrStatus:1*window.cgiData.ori_status,
HitBizuin:1*window.cgiData.hit_bizuin,
HitVid:window.cgiData.hit_vid,
SessionIdStr:window.sessionid,
Url:window.parent.window.location.href,
Device:window.devicetype
}
})),_.myPlayer=new t.mpVideoPlayer({
preview:!(1*window.cgiData.preview!==1),
isInIframe:!0,
hit_bizuin:cgiData.hit_bizuin,
hit_vid:cgiData.hit_vid,
fromid:_.scene,
ori_status:_.ori_status,
is_mp_video:window.cgiData.txvideo_vid?0:window.cgiData.is_mp_video,
plugins:p,
oriVid:_.id,
vid:window.cgiData.txvideo_vid?window.cgiData.txvideo_vid:_.id,
ckey:window.cgiData.txvideo_vid?"":_.ckey,
ckey_ad:_.ckey_ad,
width:o,
height:c,
container:"#js_mpvedio",
__biz:_.__biz,
uin:_.uin,
mid:_.mid,
idx:_.idx,
comment_id:_.comment_id,
scene_type:0,
autoplay:_.autoplay,
videoMd5:window.cgiData.video_md5,
headImgUrl:window.parent.round_head_img,
canShareVideo:!window.cgiData.is_in_pay_subscribe,
leaveReport12710Type:1,
onReady:function(){
if(_.dom.js_mpvedio.style.height="100%",(w.showVideoDetail()||w.showReprint())&&!_.hasShowBotbar){
var i=v("bottom_bar");
i&&(i.style.display="",_.hasShowBotbar=!0,e.postMessage({
type:"addVideoIframeHeight",
data:{
vid:window.cgiData.txvideo_vid||_.id,
height:_.mpVideoBotH
}
}));
}
e.postMessage({
type:"videoInited",
data:{
vid:_.id,
ori_status:_.ori_status,
hit_bizuin:cgiData.hit_bizuin,
hit_vid:cgiData.hit_vid
}
});
}
});
}
function v(i){
return document.getElementById(i);
}
i(),p(),r();
}();
});