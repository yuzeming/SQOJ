<div class="box">
	<div id="post-post">
		<div class="nifty">
		<h2>Problem List</h2>
		</div>
		<div class="en_body">
			<table class="ProbList">
				{{#PROB_LIST}}
				<tr>
					<td><a href="/problem/show/{{PORB_NAME}}">{{PORB_TITLE}}</a></td>
					<td><a href="/problem/submit/{{PORB_NAME}}">Submit</a></td>
					<td><a href="/submit/list/?pid={{PORB_ID}}&uid=me">My Submission</a></td>
				</tr>
				{{/PROB_LIST}}
			</table>
		</div>
	</div>
</div>
