<template>
    <div>
        <!-- <c1 :p3="t1"></c1>              ERROR    --> 
        <c1 :p1="t2"></c1>
    </div>
</template>

<script>
import c1 from '../components/c1.vue'
export default {
    components: {c1},
    data() {
        return{
            t1: ()=>alert('t1'),
            t2: ()=>alert('t2')
        }
    }
}
</script>