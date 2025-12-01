# PowerShell runner for all tests
param([string]$exe = "system.exe")
for ($i = 1; $i -le 24; $i++) {
    Write-Host "Running test case $i"
    & .\$exe --mode test --testcase $i
}
