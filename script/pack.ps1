if ( $args.count -eq 1 ) {
	$studentid=$args[0]
  Write-Output "Packing for $studentid"
  $compress = @{
    Path = "include", "src"
    CompressionLevel = "Optimal"
    DestinationPath = "HW1_$studentid.zip"
  }
  Compress-Archive @compress
} else {
	Write-Output "Usage: script/pack.ps1 <student_id>"
}
