# PowerShell Script to Detect Load Order Hijacking Vulnerabilities

$searchPaths = @(
    "$env:SystemRoot\System32",
    "$env:ProgramFiles",
    "$env:ProgramFiles(x86)",
    "$env:USERPROFILE"
)

$results = @()

foreach ($path in $searchPaths) {
    $executables = Get-ChildItem -Path $path -Filter "*.exe" -Recurse -ErrorAction SilentlyContinue
    
    foreach ($exe in $executables) {
        $signature = Get-AuthenticodeSignature -FilePath $exe.FullName
        
        if ($signature.Status -eq 'Valid') {
            $missingDLLs = & "C:\Windows\System32\sxstrace.exe" /q /d "$exe.FullName" 2>&1 | Select-String "not found"
            
            if ($missingDLLs) {
                $results += [PSCustomObject]@{
                    Executable = $exe.FullName
                    MissingDLLs = $missingDLLs -join ", "
                    Signature = $signature.SignerCertificate.Subject
                }
            }
        }
    }
}

$results | Format-Table -AutoSize
$results | Export-Csv -Path "C:\Users\Public\VulnerableExecutables.csv" -NoTypeInformation
