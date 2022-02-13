import Vue from 'vue'
import Router from 'vue-router'
import { normalizeURL } from '@nuxt/ufo'
import { interopDefault } from './utils'
import scrollBehavior from './router.scrollBehavior.js'

const _5336eece = () => interopDefault(import('..\\pages\\board\\index.vue' /* webpackChunkName: "pages/board/index" */))
const _12f4ff92 = () => interopDefault(import('..\\pages\\users\\index.vue' /* webpackChunkName: "pages/users/index" */))
const _7c2cd9ae = () => interopDefault(import('..\\pages\\board\\post.vue' /* webpackChunkName: "pages/board/post" */))
const _31683b47 = () => interopDefault(import('..\\pages\\board\\modify\\_id.vue' /* webpackChunkName: "pages/board/modify/_id" */))
const _52d5f1dc = () => interopDefault(import('..\\pages\\users\\profile\\_id.vue' /* webpackChunkName: "pages/users/profile/_id" */))
const _d1a8e896 = () => interopDefault(import('..\\pages\\index.vue' /* webpackChunkName: "pages/index" */))

// TODO: remove in Nuxt 3
const emptyFn = () => {}
const originalPush = Router.prototype.push
Router.prototype.push = function push (location, onComplete = emptyFn, onAbort) {
  return originalPush.call(this, location, onComplete, onAbort)
}

Vue.use(Router)

export const routerOptions = {
  mode: 'history',
  base: '/',
  linkActiveClass: 'nuxt-link-active',
  linkExactActiveClass: 'nuxt-link-exact-active',
  scrollBehavior,

  routes: [{
    path: "/board",
    component: _5336eece,
    name: "board"
  }, {
    path: "/users",
    component: _12f4ff92,
    name: "users"
  }, {
    path: "/board/post",
    component: _7c2cd9ae,
    name: "board-post"
  }, {
    path: "/board/modify/:id?",
    component: _31683b47,
    name: "board-modify-id"
  }, {
    path: "/users/profile/:id?",
    component: _52d5f1dc,
    name: "users-profile-id"
  }, {
    path: "/",
    component: _d1a8e896,
    name: "index"
  }],

  fallback: false
}

function decodeObj(obj) {
  for (const key in obj) {
    if (typeof obj[key] === 'string') {
      obj[key] = decodeURIComponent(obj[key])
    }
  }
}

export function createRouter () {
  const router = new Router(routerOptions)

  const resolve = router.resolve.bind(router)
  router.resolve = (to, current, append) => {
    if (typeof to === 'string') {
      to = normalizeURL(to)
    }
    const r = resolve(to, current, append)
    if (r && r.resolved && r.resolved.query) {
      decodeObj(r.resolved.query)
    }
    return r
  }

  return router
}
