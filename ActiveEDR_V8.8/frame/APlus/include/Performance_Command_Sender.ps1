param($command,$target,$optional,$Testcase="test",$Step="",$Tag="",$Result="")

$pipe = new-object System.IO.Pipes.NamedPipeClientStream("wwwPerfMonBase");
$pipe.Connect();
 
$sw = new-object System.IO.StreamWriter($pipe);
$cmd=$command+"ý"+$target+"ý"+$optional+"ý"+$Testcase+"ý"+$Step+"ý"+$Tag+"ý"+$Result
$sw.WriteLine($cmd);
$sw.WriteLine('exit');
 
$sw.Dispose();
$pipe.Dispose()
