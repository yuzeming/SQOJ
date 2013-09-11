<html>
<head>
	<meta http-equiv="Content-Type" content="text/html;charset=utf-8;" />
	<title>{{TITLE}}</title>
	<link rel="stylesheet" href="/style.css" type="text/css" media="screen" />
</head>

<body>
	<div id="main">
	<div id="wrapper-bg">
	<div id="wrapper">
	<div id="top">
	<div id="logo"><h1><a href="" title="{{TITLE}}">{{TITLE}}</a></h1></div>
		<div id="menu">
		<ul>
			<li id="searchbox">
			<form method="get" id="searchform" action="/go">
			<input type="text" placeholder="题号跳转..." name="pid" id="s" />
			</form>
			</li>
			<li class="current_page_item" ><a  href="/">首页</a></li>
			<li class="page_item" ><a href="/problem/list">题目</a></li>
			<li class="page_item" ><a href="/contest/list">比赛</a></li>
			{{#LOGIN}}
			<li class="page_item" ><a href="/user/login/">登陆</a></li>
			<li class="page_item" ><a href="/user/reg/">注册</a></li>
			{{/LOGIN}}
			
			{{#LOGOUT}}
			<li class="page_item"><a href="/user/show/{{SESSION_USER_ID}}/">{{SESSION_USER_NAME}}</a></li>
			<li class="page_item" ><a href="/user/logout/">登出</a></li>
			{{/LOGOUT}}
			 
		</ul>
		</div>
	</div>
	</div>
	</div>
<div id="content">
	{{CONTENT}}
</div>

<div class="space"></div>
<div id="footer">
	<div class="footer">
			<p class="fooleft">	YuZeming@Gmail.com SQOJ	</p>
		<p class="fooright"><a href="#top" title="Top">top</a></p>
	</div>
</div>
</body>
</html>
