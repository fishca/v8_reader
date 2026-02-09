$content = Get-Content 's:/work/CPP/BDS13/### refactoring ###/v8reader_cur/MainUnit.cpp' -Raw
$oldPattern = @'
					else if (categoryCom.name == md_Roles)
					{
						// Для Roles используем MainForm->Roles (vector<String>), так как mdRoles не заполняется
						childDataCom->Name = MainForm->Roles[i];
						childDataCom->text_module = L"";
					}
					else if (categoryCom.name == md_SessionParameters)
'@
$newPattern = @'
					else if (categoryCom.name == md_SessionParameters)
'@
$content = $content -replace [regex]::Escape($oldPattern), $newPattern
Set-Content -Path 's:/work/CPP/BDS13/### refactoring ###/v8reader_cur/MainUnit.cpp' -Value $content
Write-Host "Fix applied"
