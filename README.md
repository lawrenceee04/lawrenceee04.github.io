# Cloudflare Pages + Workers Migration

This repository now uses Cloudflare Pages for static hosting and Cloudflare Workers for the API endpoints.

## What changed
- Frontend now calls `/api/gravatar` and `/api/github` instead of Netlify function paths.
- `worker.js` contains the Cloudflare Worker handlers for Gravatar and GitHub.
- `wrangler.toml` configures Wrangler for local development and deploys.
- `package.json` no longer depends on Netlify-specific packages.

## Deploying the static site
1. On Cloudflare Pages, configure the repository.
2. Build command: `npm run build`
3. Publish directory: `dist`

## Deploying the Worker
1. Install dependencies: `npm install`
2. Run locally: `npm run dev:worker`
3. Deploy: `npm run deploy:worker`

## API secrets
Set these Cloudflare Worker secrets after you log in:

```bash
wrangler secret put GITHUB_API_KEY
wrangler secret put GRAVATAR_API_KEY
```

If `GITHUB_API_KEY` is not provided, the worker will still attempt an unauthenticated request, but using the token is recommended.

## Notes
- If you want the same domain for both Pages and the Worker, route `/api/*` to the worker from your Cloudflare dashboard or use a custom domain with a worker route.
- The static app still builds with Vite and publishes from `dist`.

## Same-domain Pages + Worker routing example
For a single domain like `example.com`, map all API requests to the worker while serving static files from Pages.

1. Deploy the Pages site normally.
2. Deploy the worker and configure a Cloudflare route for `/api/*`.

Example `wrangler.toml` route config:

```toml
name = "lawrenceee04-pages-api"
main = "worker.js"
compatibility_date = "2026-06-28"
type = "javascript"
# Uncomment these to deploy the worker to your custom domain route
# account_id = "<YOUR_CLOUDFLARE_ACCOUNT_ID>"
# zone_id = "<YOUR_ZONE_ID>"
# route = "example.com/api/*"
```

With this setup:
- `https://example.com` serves the Pages site
- `https://example.com/api/github` and `/api/gravatar` are routed to the worker
- browser requests to `/api/*` are handled by the worker while all other paths remain static
