<template>
    <div>
        <h1>c1 컴포넌트</h1>
        <button @click="p1">클릭{{p4.message}}</button>
    </div>
</template>

<script>
export default {
    props: {
        p1: [Number, String, Boolean, Function, Object, Array, Symbol],
        p2: {
            type: String,
            required: false
        },
        p3: {
            type: Number,
            default: 100
        },
        p4: {
            type: Object,
            default: function(){
                return{
                    message: 'hello world'
                }
            }
        },
        p5: {
            validator: (v) => v > 0
        }
    }
}
</script>