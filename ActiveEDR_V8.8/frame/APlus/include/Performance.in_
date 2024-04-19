[+] void Perf(string command,string target optional, string option optional,string Testcase optional,string Step optional,string Tag optional,string Result optional)
	[ ] list of STRING ls
	[ ] string sPath=StrTran(currentpath,"\","'\'")
	[ ] sPath=StrTran(sPath,":'\",":\")+"'"
	[+] if(Tag==NULL)
		[ ] Tag=""
	[ ] //print("PowerShell.exe -command {sPath}\Performance_Command_Sender.ps1 -command '{command}' -target '{target}' -optional '{option}' -Testcase '{Testcase}' -Step '{Step}' -Tag '{Tag}'")
	[ ] Sys_Execute("PowerShell.exe -command {sPath}\Performance_Command_Sender.ps1 -command '{command}' -target '{target}' -optional '{option}' -Testcase '{Testcase}' -Step '{Step}' -Tag '{Tag}'",ls)
[+] testcase s1()
	[ ] list of STRING ls
	[ ] //Sys_Execute("powershell.exe set-executionpolicy unrestricted -force",ls)
	[ ] listprint(ls)
	[ ] Perf("Memory","AspenPlus","no option","this is a test case","this is a step")
	[ ] 
	[ ] 
[ ] 
[ ] 
