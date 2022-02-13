<template>
    <div>
        <c1 :text="msg1"></c1>
        <c1 :text="msg2"></c1>
    </div>
</template>

<script>
import c1 from '../components/c1.vue'
export default {
    components: {c1},
    data() {
        return{
            msg1: 'hello',
            msg2: 'world'
        }
    }
}
</script>