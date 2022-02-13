# install.packages("stringr")
library(stringr)

### file 읽어오기

PATH = "R/KakaoTalkChats.txt"

raw_data = readLines(PATH, encoding="UTF-8")

info = raw_data[1:2]
title = str_split(info[1], ' ')[[1]][1]

idx = raw_data[3:length(raw_data)] != ''
chats = raw_data[3:length(raw_data)][idx]
# print(str(chats))

# 차누야이의 챗 로그 분석
chat.chanwoo = data.frame()
# print(str(chat.chanwoo))

for (i in 1:length(chats)){
    chat = str_split(chats[i], ' ', 6)[[1]]
    date = chat[1:5]
    names(date) = c('year', 'month', 'date', 'is.afternoon', 'time')

    if(date['is.afternoon'] == '오전') date['is.afternoon'] = F
    else date['is.afternoon'] = T

    if(str_sub(date['time'], -1,-1) == ','){
        date['time'] = substring(date['time'], 1, (nchar(date['time'])-1))
        # print(date)
        chat = str_split(chat[6], ' ',3)[[1]]
        name = chat[1]
        context = chat[3]
        # print(chat)
        if(name == '김찬우'){
            chat.chanwoo = rbind(chat.chanwoo, cbind(t(date), context))
        }
    }else{
        # print(date)
    }
}
colnames(chat.chanwoo) = c('year', 'month', 'date', 'is.afternoon', 'time', 'log')
print(sort(table(chat.chanwoo$log), decreasing=T))
