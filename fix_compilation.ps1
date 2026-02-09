# PowerShell script to fix MainUnit.cpp compilation error
$filePath = "s:/work/CPP/BDS13/### refactoring ###/v8reader_cur/MainUnit.cpp"

# Read the file content
$content = Get-Content -Path $filePath -Raw

# Find and remove the problematic block for Roles that uses undefined 'i'
# This block is inside a range-based for loop where 'i' is not defined
# The correct Roles handling is already at lines 1323-1335

$pattern = '\s+else if \(categoryCom\.name == md_Roles\)\s+\{\s+// Для Roles используется MainForm->Roles \(vector<String>\), так как mdRoles не заполняется\s+childDataCom->Name = MainForm->Roles\[i\];\s+childDataCom->text_module = L"";\s+\}\s+'

$replacement = ''

$newContent = $content -replace $pattern, $replacement

# Write the fixed content back
Set-Content -Path $filePath -Value $newContent -NoNewline -Encoding UTF8

Write-Host "Fixed MainUnit.cpp - removed problematic Roles block"
