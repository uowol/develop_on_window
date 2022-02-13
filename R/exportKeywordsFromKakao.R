library(stringr)

PATH = "R/KakaoTalkChats_주임.txt"

data = readLines(PATH, encoding="UTF-8")

chat_date = grep("-+ 20\\d+년 \\d+월 \\d+일 [가-힣]+요일 -+", data)

chat_invite = grep(".+님이 .+님을 초대하였습니다.", data)

chat_left = grep('.+님이 나갔습니다.', data)

idx_chat = grep("\\[.+\\] \\[오전?후? \\d+:\\d+\\] .+", data)

filter = unique(c(chat_date, chat_invite, chat_left))

res = c()
context = ''
for(i in 4:length(data)){
    if(i %in% filter) next
    if(i %in% idx_chat){
        temp = str_split(data[i], '] ')[[1]]
        name = substring(temp[1], 2)
        time = substring(temp[2], 2)
        context = temp[3]
        # print(paste(name, time))
    }
    if(context == '') context = data[i]
    if(grepl("^이모티콘$", context)) next
    else if(grepl("^사진$", context)) next
    else if(grepl("^사진 \\d+장$", context)) next
    else if(grepl("^동영상$", context)) next

    keywords = str_split(context, ' ')[[1]]
    for(keyword in keywords){
        if(grepl("https?://", keyword)) next
        keyword = gsub("[^가-힣a-zA-Zㄱ-ㅎ0-9]","", keyword)
        # print(keyword)
        if(keyword == '') next
        if(!(keyword %in% names(res))) res[keyword] = 0
        res[keyword] = res[keyword] + 1
    }
    # res[][[1]] = c(chat_list[name][[1]], context)
    context = ''
}

library(jsonlite)

sorted_res = sort(res[res>1], decreasing=T)
export.json = toJSON(data.frame(t(sorted_res)), encoding='UTF-8')
write(export.json, file="keywords_from_kakao.json")

# print(head(sorted_res, 10))
ranked_res = data.frame(t(head(sorted_res, 100)))
export.json = toJSON(ranked_res, encoding='UTF-8')
write(export.json, file="keywords_from_kakao_ranked.json")