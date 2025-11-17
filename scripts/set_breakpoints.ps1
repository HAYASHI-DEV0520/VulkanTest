param(
    [string]$File = "C:\Users\user\source\repos\HAYASHI-DEV0520\VulkanTest\VulkanTest\VulkanTest.cpp"
)

# Visual Studio の DTE ProgID 候補（必要に応じて順序を変更）
$progCandidates = @("VisualStudio.DTE.18.0","VisualStudio.DTE.17.0","VisualStudio.DTE.16.0")
$dte = $null
foreach ($p in $progCandidates) {
    try {
        $dte = [Runtime.InteropServices.Marshal]::GetActiveObject($p)
        break
    } catch { }
}

if (-not $dte) {
    Write-Error "Visual Studio の DTE に接続できません。Visual Studio を起動してから再実行してください。"
    exit 1
}

# ファイルを Visual Studio で開く（既に開かれていても OK）
try {
    $dte.ItemOperations.OpenFile($File) > $null
} catch {
    Write-Warning "ファイルを開けませんでしたが、ブレークポイントの追加は試行します。"
}

# ファイル内容を行単位で取得して非空行にブレークポイントを追加
$lines = Get-Content -LiteralPath $File -ErrorAction Stop -Encoding UTF8
$added = 0
for ($i = 0; $i -lt $lines.Count; $i++) {
    if ($lines[$i].Trim() -ne "") {
        $lineNum = $i + 1
        # DTE.Debugger.Breakpoints.Add(Function, File, Line, Column, Condition, ConditionType, HitCount, Language)
        $dte.Debugger.Breakpoints.Add("", $File, $lineNum, 1) > $null
        $added++
    }
}

Write-Host "完了: $added 個のブレークポイントを追加しました。__Debug > Windows > Breakpoints__ で確認できます。"