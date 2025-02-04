const getAvatarUrl = async (profileIdentifier) => {
    try {
        const response = await fetch('/.netlify/functions/gravatarAPI', {
            method: 'GET',
            headers: {
                'Content-Type': 'application/json',
                profileIdentifier: profileIdentifier,
            },
        });
        const data = await response.json();
        const avatar_url = `${data.avatar_url}?s=300`;

        // Set avatar image source
        document.getElementById('gravatar-avatar').src = avatar_url;
    } catch (error) {
        console.error('Error:', error);
    }
};

const getVerifiedAccounts = async (profileIdentifier) => {
    try {
        const response = await fetch('/.netlify/functions/gravatarAPI', {
            method: 'GET',
            headers: {
                'Content-Type': 'application/json',
                profileIdentifier: profileIdentifier,
            },
        });
        const data = await response.json();
        const verified_accounts = data.verified_accounts;
        return verified_accounts;
    } catch (error) {
        console.error('Error:', error);
    }
};

// Gravatar Avatar
getAvatarUrl('lawrencegarciaaa');

// Verified Accounts
getVerifiedAccounts('lawrencegarciaaa').then((verifiedAccounts) => {
    verifiedAccounts.forEach((account, index) => {
        const card = document.createElement('a');
        // set attributes
        card.href = account.url;
        card.target = '_blank';
        card.className =
            'flex flex-col snap-center border shrink-0 w-full sm:w-1/4 justify-center items-center text-lg md:text-2xl rounded';
        card.id = `social-${index}`;

        // set text
        const text = document.createTextNode(account.service_label);
        card.appendChild(text);

        // set card
        const socials_list = document.getElementById('socials-list');
        socials_list.appendChild(card);
    });
});

// GitHub Repositories
const getGitHubRepos = async () => {
    try {
        const response = await fetch('/.netlify/functions/githubAPI');
        const data = await response.json();
        return data;
    } catch (error) {
        console.error('Error:', error);
    }
};

getGitHubRepos().then((repos) => {
    repos.forEach((repo, index) => {
        if (repo.visibility === 'public') {
            const card = document.createElement('a');
            // set attributes
            card.id = `repo-${index}`;
            card.href = repo.html_url;
            card.className = 'text-xl font-bold p-4 border rounded h-52 md:h-48 overflow-hidden shadow-md';
            card.target = '_blank';

            const textDiv = document.createElement('div');
            textDiv.className = 'flex items-center gap-3';

            const repoNameDiv = document.createElement('div');
            repoNameDiv.className = 'text-lg font-bold';
            const repoNameText = document.createTextNode(repo.name);
            repoNameDiv.appendChild(repoNameText);

            const repoTypeDiv = document.createElement('div');
            repoTypeDiv.className = 'text-xs font-light border rounded-full py-1 px-2';
            const repoTypeText = document.createTextNode(repo.visibility);
            repoTypeDiv.appendChild(repoTypeText);

            const descriptionDiv = document.createElement('div');
            descriptionDiv.className = 'text-lg font-medium';
            const descriptionText = document.createTextNode(repo.description ? repo.description : 'N/A');
            descriptionDiv.appendChild(descriptionText);

            textDiv.appendChild(repoNameDiv);
            textDiv.appendChild(repoTypeDiv);

            card.appendChild(textDiv);
            card.appendChild(descriptionDiv);

            const reposList = document.getElementById('repos-list');
            reposList.appendChild(card);
        }
    });
});
