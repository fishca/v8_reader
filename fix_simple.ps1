# Simple fix script - removes lines 1300-1305 from MainUnit.cpp
$lines = Get-Content -Path "s:/work/CPP/BDS13/### refactoring ###/v8reader_cur/MainUnit.cpp"

# Find the line numbers to remove
$startLine = -1
$endLine = -1

for ($i = 0; $i -lt $lines.Count; $i++) {
    if ($lines[$i] -match 'else if \(categoryCom\.name == md_Roles\)') {
        $startLine = $i
        # Find the end of this block
        for ($j = $i; $j -lt $lines.Count; $j++) {
            if ($lines[$j] -match 'else if \(categoryCom\.name == md_SessionParameters\)') {
                $endLine = $j - 1  # End before the SessionParameters line
                break
            }
        }
        break
    }
}

if ($startLine -ge 0 -and $endLine -ge $startLine) {
    # Remove lines from startLine to endLine (inclusive)
    $newLines = @()
    for ($i = 0; $i -lt $lines.Count; $i++) {
        if ($i -lt $startLine -or $i -gt $endLine) {
            $newLines += $lines[$i]
        }
    }

    # Write back
    $newLines | Set-Content -Path "s:/work/CPP/BDS13/### refactoring ###/v8reader_cur/MainUnit.cpp" -Encoding UTF8
    Write-Host "Removed problematic lines $($startLine+1) to $($endLine+1)"
} else {
    Write-Host "Could not find the problematic block"
}
