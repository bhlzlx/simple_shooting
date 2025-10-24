local t = "got item {{item_1}} and {{item_2}} "

local parsedText, variables = parseTextArgs(t)

return parsedText, variables
