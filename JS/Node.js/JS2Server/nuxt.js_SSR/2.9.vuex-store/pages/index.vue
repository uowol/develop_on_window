<template>
    <div>
        <button @click="$store.commit('increment', 2)">{{count}}</button>
    </div>
</template>

<script>
import {mapState} from 'vuex'

export default {
    computed: mapState(['count']),
    fetch ({store}){    // excuted before rendering page. So we can't use 'this' in here.
        console.log('Test')
        store.commit('init', 2)
    }
}
</script>