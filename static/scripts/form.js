function addt()
{
	let addteacher = document.getElementById('addteacher');
	let tdiv = document.createElement('div');
	let tname = document.getElementById('teacher').value;
	tdiv.classList.add('col');
	tdiv.innerHTML = "" +
	"<h1 class='title boxtitle'>Teacher "+tname+"</h1>" +
	"<label class = 'par labpar' for = 'p:"+tname+":schedules per week'> Schedules per week (integer number): </label>" +
	"<input name = 'p:"+tname+":schedules per week' type = 'number' class = 'intxt' />" +
	"<label class = 'par labpar' for = 'p:"+tname+":subj'> Subjects (format: \"class - sub.\", comma separated): </label>" +
	"<input name = 'p:"+tname+":subj' type = 'text' class = 'intxt' />";
	addteacher.appendChild(tdiv);
}