# Sys.setlocale("LC_CTYPE", "ko_KR.UTF-8")

# regular expressions
library(stringr)

PATH = "R/KakaoTalkChats_엄마.txt"

data = readLines(PATH, encoding="UTF-8")

chat_date = grep("-+ 20\\d+년 \\d+월 \\d+일 [가-힣]+요일 -+", data)
# print(chat_date)

chat_invite = grep(".+님이 .+님을 초대하였습니다.", data)
# print(chat_invite)

chat_left = grep('.+님이 나갔습니다.', data)

idx_chat = grep("\\[.+\\] \\[오전?후? \\d+:\\d+\\] .+", data)
# print(idx_chat)

chat_list = list()
context = ''
for(i in 4:length(data)){
    if(i %in% chat_date || i %in% chat_invite || i %in% chat_left) next
    if(i %in% idx_chat){
        temp = strsplit(data[i], '] ')[[1]]
        name = substring(temp[1], 2)
        time = substring(temp[2], 2)
        context = temp[3]
        # print(paste(name, time))
    }
    if(context == '') context = data[i]
    chat_list[name][[1]] = c(chat_list[name][[1]], context)
    context = ''
}
# print(str(chat_list))
# print(lapply(chat_list, length))
# print(lapply(chat_list, function(x) length(which(x == "사진"))))


# JSON파일로 내보내기
# install.packages("jsonlite")
library(jsonlite)
export.json = toJSON(chat_list, encoding='utf-8')
write(export.json, file="export.json")