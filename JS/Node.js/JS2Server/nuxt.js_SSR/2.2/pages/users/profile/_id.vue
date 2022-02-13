<template>
    <h1>유저 id: {{id}} 프로필 </h1>
</template>
<script>
export default {
    validate({params}){ // 넘어오는 많은 데이터 중 params만 가져오쟈
        if(!isNaN(params.id)){
            return true
        }else return false
    },
    data() {
        return {
            id: this.$route.params.id
        }
    }
}
</script>