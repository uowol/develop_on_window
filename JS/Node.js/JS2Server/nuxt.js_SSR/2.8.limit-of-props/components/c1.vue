<template>
    <div>
        <h1>c1 컴포넌트 {{message}}</h1>
        <button @click="increment">index 증가</button>
        <hr>
    </div>
</template>

<script>
export default {
    props: {
        message: {
            type: Number
        },
        increment: {
            type: Function
        }
    },
    methods:{
        _increment() {
            this.message += 1
        }
    }
}
</script>